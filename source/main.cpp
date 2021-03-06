#include <iostream>
#include <memory>
#include <irrlicht.h>
#include <Game3DFactory.h>
#include <Game3D.h>
#include <GameDesc.h>
#include <Task.h>
#include <functional>
#include <algorithm>

using namespace std;

using namespace irr;

using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;


class GameBaba{

private:
    IrrlichtDevice* device;
    IVideoDriver* driver;
    ISceneManager* smgr;
    IGUIEnvironment* guienv;
    std::shared_ptr<Game3DFactory> factory;
    GameDesc gameDesc;
    std::shared_ptr<Game3D> game3D = 0;

    //lambda function used as variable 'taskExec'. And capturing the 'this' variable too
    std::function<bool(Task<VectorInt>)> taskExec = [this](Task<VectorInt>  t){
        if(t.time >= this->device->getTimer()->getTime()){
            t.exec(t.param);
            t.time += t.interval;
        }
        return !t.repeat;
    };

    public:

    void init(){

    	this->device =
		createDevice(EDT_OPENGL, core::dimension2d<u32>(640, 480), 16, false);

        /*
        Set the caption of the window to some nice text. Note that there is
        a 'L' in front of the string. The Irrlicht Engine uses wide character
        strings when displaying text.
        */
        this->device->setWindowCaption(L"GameBaba World");

        /*
        Get a pointer to the video driver, the SceneManager and the
        graphical user interface environment, so that
        we do not always have to write device->getVideoDriver(),
        device->getSceneManager() and device->getGUIEnvironment().
        */
        this->driver = this->device->getVideoDriver();
        this->smgr = this->device->getSceneManager();
        this->guienv = this->device->getGUIEnvironment();
    };


    void run(){

        this->device->setResizable(true);

        int lastFPS = -1;
        /*
        Ok, now we have set up the scene, lets draw everything:
        We run the device in a while() loop, until the device does not
        want to run any more. This would be when the user closed the window
        or pressed ALT+F4 in windows.
        */

        while(this->device->run())
        {
            if (this->device->isWindowActive())
            {
                 this->handleTasks();

                /*
                Anything can be drawn between a beginScene() and an endScene()
                call. The beginScene clears the screen with a color and also the
                depth buffer if wanted. Then we let the Scene Manager and the
                GUI Environment draw their content. With the endScene() call
                everything is presented on the screen.
                */
                this->driver->beginScene(true, true, SColor(0,200,200,200));

                this->smgr->drawAll();
                this->guienv->drawAll();

                this->driver->endScene();

                int fps = this->driver->getFPS();

                if (lastFPS != fps)
                {
                    core::stringw tmp(L"GameBaba World ");
                    //tmp += driver->getName();
                    tmp += L" - fps: ";
                    tmp += fps;

                    this->device->setWindowCaption(tmp.c_str());
                    lastFPS = fps;
                }
            }
        }

        /*
        After we are finished, we have to delete the Irrlicht Device
        created before with createDevice(). In the Irrlicht Engine,
        you will have to delete all objects you created with a method or
        function which starts with 'create'. The object is simply deleted
        by calling ->drop().
        See the documentation at
        http://irrlicht.sourceforge.net//docu/classirr_1_1IUnknown.html#a3
        for more information.
        */

    };

    void handleTasks(){

        if(this->game3D != 0){//making sure the game3D object is already created before accessing it in this block
            //handle registered tasks
            for(unsigned int i=0; i<this->game3D->tasks.size(); i++){
                if(this->taskExec(this->game3D->tasks[i])){//remove task
                    //remove the nth element
                    this->game3D->tasks.erase(this->game3D->tasks.begin()+i);
                    i--;
                }
            }

            /* OR - the above for loop is more efficient
            if(this->game3D->tasks.size() > 0){
                vector<Task<VectorInt>>::iterator new_end = std::remove_if(this->game3D->tasks.begin(),
                                                this->game3D->tasks.end(),
                                                this->taskExec);
                //must call the erase method
                this->game3D->tasks.erase(new_end, this->game3D->tasks.end());
            }*/


        }


    };

    void quit(){

        /* Cleanup */
        this->device->setEventReceiver(0);
        this->device->closeDevice();
        this->device->drop();
    }

    GameDesc createGameDesc(std::string data){
        //ROUGH IMPLEMENTATION
        if(data == ""){
            //default
            this->gameDesc.game = "chess";
            this->gameDesc.userSide = "w";
            this->gameDesc.variant = "INTERNATIONAL_DRAUGHTS";//for draughts
            this->gameDesc.boardPosition = "";
            this->gameDesc.flip = false; //if false if the user is white otherwise true - if false it means the white is directly close to the player
            this->gameDesc.isOffsetSelection = false;//for only smart phones and tablets of medium size .Now make the z offset allow easy pick of piece especially on small device
            this->gameDesc.boardTheme = "";
            this->gameDesc.pieceTheme = "";
        }else{

            //TODO

        }

        return this->gameDesc;

    };

    /*
     Called by external program. Can also be called locally
    */
    void show(std::string data){
            this->createGameDesc(data);
            this->factory = std::shared_ptr<Game3DFactory>(new Game3DFactory(this->device, this->driver, this->smgr, this->guienv));
            this->game3D = this->factory->create(this->gameDesc);
    };


};

int main(int argc, char** argv)
{
    GameBaba g;
    g.init();
    g.show("");
    g.run();
    g.quit();

    return 0;
}

