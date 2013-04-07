#include "loader.h"



int main(int argc, char *argv[])
{
    qDebug() << argc << ", " << argv;
    if(argc <= 1){
        //        Loader app;
        //        try {
        //            app.start();
        //        } catch( Ogre::Exception& e ) {
        //            std::cerr << "An exception has occured: " <<
        //                         e.getFullDescription().c_str() << std::endl;

        //        }
        return 1;
    }
    else{
            Loader app(QString::fromStdString(argv[1]));
        if(QString(argv[1])==QString("reconfigure")){
            try {
                qDebug() << "argv = " << argv[1];
                app.reconfigure();
            } catch( Ogre::Exception& e ) {
                std::cerr << "An exception has occured: " <<
                             e.getFullDescription().c_str() << std::endl;

            }
        }
        else {
            try {
                app.start();
            } catch( Ogre::Exception& e ) {
                std::cerr << "An exception has occured: " <<
                             e.getFullDescription().c_str() << std::endl;

            }


        }
    }

    return 0;
}
