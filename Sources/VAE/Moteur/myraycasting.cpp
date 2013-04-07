#include "myraycasting.h"

MyRayCasting::MyRayCasting()
{
}

unsigned int MyRayCasting::RaycastFromRay(Ogre::Ray &camRay,Ogre::Entity *pentity, Ogre::Vector3 &result, int &distance)
{

    Ogre::Real closest_distance = -1.0f; //Distance la plus courte possible (on met un chiffre négatif pour que toute les distances soient acceptées)
    Ogre::Vector3 closest_result; //Point de collision le plus proche

    //Information du mesh à trouver
    size_t vertex_count; //Nombre de point
    size_t index_count;
    Ogre::Vector3 *vertices;
    unsigned long *indices;

    //Nombre d'impact sur le mesh
    unsigned int nbImpact = 0;

    //Obtention des informations du mesh
    getMeshInformation(pentity->getMesh(), vertex_count, vertices, index_count, indices,
                       pentity->getParentNode()->_getDerivedPosition(),
                       pentity->getParentNode()->_getDerivedOrientation(),
                       pentity->getParentNode()->_getDerivedScale());

    //Test de chaque triangle du mesh
    bool new_closest_found = false; //Indique si un point de collision plus proche est trouvé
    for(int i = 0; i < static_cast<int>(index_count); i += 3) //Pour chaque triangle
    {
        //Vérifier si le rayon est en collision avec le triangle
        std::pair<bool, Ogre::Real> hit = Ogre::Math::intersects(camRay, vertices[indices[i]], vertices[indices[i+1]], vertices[indices[i+2]], true, false);

        //S'il y a une une collision avec le triangle
        if(hit.first)
        {
            nbImpact++;
            //Si l'impact le plus proche est à distance négative ou que le second impact à une distance plus courte
            if(hit.second)
                nbImpact++;
            if((closest_distance < 0.0f) || (hit.second < closest_distance))
            {
                //C'est la plus courte distance, on la sauvegarde
                closest_distance = hit.second;
                new_closest_found = true; //On mentionne que l'on a trouvé un point d'impact plus près
            }
        }
    }

    //On libère de la mémoire les vertices et indices
    delete[] vertices;
    delete[] indices;

    //Si on a trouvé une distance plus courte, on met à jour le résultat avant de passer à l'autre objet
    if(new_closest_found)
        closest_result = camRay.getPoint(closest_distance); //On obtient le point d'impact à partir du rayon et la distance à parcourrir


    //On retourne le résultat
    if(closest_distance >= 0.0f) //Si on a une distance positive (si on a au moins une collision)
    {
        result = closest_result; //Initialisation du point d'impact
        distance = closest_distance;
        return nbImpact;
    }
    else //Si le raycast n'a rien donné on retourne 0
        return nbImpact;
}

void MyRayCasting::getMeshInformation(  Ogre::MeshPtr mesh,
                                        size_t &vertex_count,
                                        Ogre::Vector3* &vertices,
                                        size_t &index_count,
                                        unsigned long* &indices,
                                        const Ogre::Vector3 &position,
                                        const Ogre::Quaternion &orient,
                                        const Ogre::Vector3 &scale)
{
    bool added_shared = false; //Les points partagés ne sont pas ajoutés
    size_t current_offset = 0;
    size_t shared_offset = 0;
    size_t next_offset = 0;
    size_t index_offset = 0;

    vertex_count = index_count = 0;

    //Calcul du nombre de points et d'indices : pour i de 0 au nombre de sous meshs
    for(unsigned short i = 0; i < mesh->getNumSubMeshes(); i++)
    {
        Ogre::SubMesh *subMesh = mesh->getSubMesh(i); //On obtient le sous mesh

        //Si le sous mesh contient des points partagés avec les autres
        if(subMesh->useSharedVertices)
        {
            if(!added_shared) //S'il n'y a pas encore de partage de point
            {
                vertex_count += mesh->sharedVertexData->vertexCount; //On ajoute le nombre de points partagés au mesh
                added_shared = true; //On indique que les points partagés sont ajoutés
            }
        }
        else //S'il n'y a pas de partage de point
            vertex_count += subMesh->indexData->indexCount; //On ajoute le nombre de point du subMesh au mesh

        //On ajoute un indice
        index_count += subMesh->indexData->indexCount;
    }

    vertices = new Ogre::Vector3[vertex_count]; //Création du tableau de points
    indices = new unsigned long[index_count]; //Création du tableau d'indices

    added_shared = false; //On considère que les point partagés ne sont plus ajoutés

    //Ajout des points et indices dans les tableaux
    for(unsigned short i = 0; i < mesh->getNumSubMeshes(); i++)
    {
        Ogre::SubMesh *subMesh = mesh->getSubMesh(i); //On obtient le sous mesh

        //Si le sous mesh a des points partagés, ont obtient les points partagés du mesh, sinon on obtient les points du sous mesh
        Ogre::VertexData *vertex_data = subMesh->useSharedVertices ? mesh->sharedVertexData : subMesh->vertexData;

        //Si le sous mesh n'a pas de points partagés ou qu'il en a mais que les points partagés ne sont pas ajoutés
        if((!subMesh->useSharedVertices) || (subMesh->useSharedVertices && !added_shared))
        {
            if(subMesh->useSharedVertices)
            {
                added_shared = true; //Les points partagés sont ajoutés
                shared_offset = current_offset;
            }

            const Ogre::VertexElement *posElem = vertex_data->vertexDeclaration->findElementBySemantic(Ogre::VES_POSITION);

            Ogre::HardwareVertexBufferSharedPtr vbuf = vertex_data->vertexBufferBinding->getBuffer(posElem->getSource());

            unsigned char *vertex = static_cast<unsigned char*>(vbuf->lock(Ogre::HardwareBuffer::HBL_READ_ONLY));

            float *preal;

            //Pour chaque point, on l'ajoute dans le tableau de point
            for(size_t j = 0; j < vertex_data->vertexCount; j++, vertex += vbuf->getVertexSize())
            {
                posElem->baseVertexPointerToElement(vertex, &preal);
                Ogre::Vector3 pt(preal[0], preal[1], preal[2]);
                vertices[current_offset + j] = (orient * (pt * scale)) + position;
            }

            vbuf->unlock();
            next_offset += vertex_data->vertexCount;
        }

        Ogre::IndexData *index_data = subMesh->indexData;
        size_t numTris = index_data->indexCount / 3;
        Ogre::HardwareIndexBufferSharedPtr ibuf = index_data->indexBuffer;

        if(ibuf.isNull()) continue;

        bool use32bitindexes = (ibuf->getType() == Ogre::HardwareIndexBuffer::IT_32BIT);

        unsigned long *pLong = static_cast<unsigned long*>(ibuf->lock(Ogre::HardwareBuffer::HBL_READ_ONLY));
        unsigned short *pShort = reinterpret_cast<unsigned short*>(pLong);

        size_t offset = (subMesh->useSharedVertices)? shared_offset : current_offset;
        size_t index_start = index_data->indexStart;
        size_t last_index = numTris*3 + index_start;

        if(use32bitindexes)
        {
            for(size_t k = index_start; k < last_index; k++)
                indices[index_offset++] = pLong[k] + static_cast<unsigned long>(offset);
        }
        else
        {
            for(size_t k = index_start; k < last_index; k++)
                indices[index_offset++] = static_cast<unsigned long>(pShort[k]) + static_cast<unsigned long>(offset);
        }

        ibuf->unlock();
        current_offset = next_offset;
    }
}
