#include <engine/common.h>
#include <engine/renderer.h>
#include <engine/meshloader.h>
#include <engine/skeletonobject.h>
#include <engine/skeletizer.h>

int amount = 1;

void shaderObjectFunc(Object& o){
    o.lightSources->pushToShaderByIndex(o.shader, 0, "lightPos0");
}
void shaderSklObjectFunc(SkeletonObject& o){
    o.lightSources->pushToShaderByIndex(o.shader, 0, "lightPos0");
}
void drawFrame(Renderer& r){
    static Object* currObj;
    static SkeletonObject* currSklObj;
    ///////////////////////////////
    r.bindFramebufferByIndex(0, 1);

    currSklObj = r.getSkeletonObjectByIndex(0);
    currSklObj->draw(shaderSklObjectFunc);

    r.getObjectByName("sphere")->position->moveTo((r.view->getCamera().location + r.view->getCamera().front));
    r.getObjectByName("sphere")->draw(shaderObjectFunc);

//    r.skyboxes->at(0)->skyboxTexture->pushToShader(currObj->shader, 0, "skybox");
    r.skyboxes->at(0)->draw();
    ///////////////////////////////
    r.bindDefaultFramebuffer();

    currObj = r.getObjectByName("screen");
    currObj->draw(shaderObjectFunc);
    ///////////////////////////////
    static float defaultSpeed = r.view->getCamera().movementSpeed;

    bool isShiftPressed = false;
    setEvent(r.window->getWindowPtr(), LEFT_SHIFT, isShiftPressed = true);
    if(isShiftPressed){
        r.view->getCamera().movementSpeed = defaultSpeed * 2;
    }
    bool isCtrlPressed = false;
    setEvent(r.window->getWindowPtr(), LEFT_CONTROL, isCtrlPressed = true);
    if(isCtrlPressed){
        r.view->getCamera().movementSpeed = defaultSpeed / 3;
    }
    if(!isShiftPressed && !isCtrlPressed){
        r.view->getCamera().movementSpeed = defaultSpeed;
    }

    setEvent(r.window->getWindowPtr(), F, r.lightSources->getByName("default")->lightPos = r.view->getCamera().location);

    setEvent(r.window->getWindowPtr(), J, if(someCounter + 1 <= 20) someCounter += 1.f/10.f; cout << someCounter << endl);
    setEvent(r.window->getWindowPtr(), K, if(someCounter - 1 >= 0) someCounter -= 1.f/10.f; cout << someCounter << endl);

    glm::vec3 sphereLoc = r.getObjectByName("sphere")->position->getLocation();
    setEvent(r.window->getWindowPtr(), P, cout << sphereLoc.x << " " << sphereLoc.y << " " << sphereLoc.z << endl);

    setEvent(r.window->getWindowPtr(), 1, currSklObj->buffer->getMesh().joints.getById(someCounter).rotate(0,-1,0));
    setEvent(r.window->getWindowPtr(), 2, currSklObj->buffer->getMesh().joints.getById(someCounter).rotate(0,1,0));
    setEvent(r.window->getWindowPtr(), 3, currSklObj->buffer->getMesh().joints.getById(someCounter).rotate(0,0,-1));
    setEvent(r.window->getWindowPtr(), 4, currSklObj->buffer->getMesh().joints.getById(someCounter).rotate(0,0,1));
    setEvent(r.window->getWindowPtr(), 5, currSklObj->buffer->getMesh().joints.getById(someCounter).rotate(-1,0,0));
    setEvent(r.window->getWindowPtr(), 6, currSklObj->buffer->getMesh().joints.getById(someCounter).rotate(1,0,0));

    setEvent(r.window->getWindowPtr(), I, cout << currSklObj->buffer->getMesh().joints.genPoseInfo() << endl);
    setEvent(r.window->getWindowPtr(), U, currSklObj->buffer->getMesh().joints.setDafaultPose());
    setEvent(r.window->getWindowPtr(), Y, currSklObj->buffer->getMesh().joints.at(someCounter)->setDefaultPose());
}

int main (){
    int window_width = 1366;
    int window_height = 768;

    Renderer renderer(window_width, window_height);
    MeshLoader meshLoader;
    MeshList meshList;
    SkeletonMeshList skeletonList;
    Skeletizer skeletizer;
    ShaderList shaders;
    TextureList tex;
    MaterialList materials;

    meshList.push(meshLoader.load("C:\\EngPathReq\\might_beeeeeeeeeeee\\models\\Character_A1016A457\\aaa.obj", "loaded"));
    meshList.push(meshLoader.load("C:\\EngPathReq\\might_beeeeeeeeeeee\\models\\skybox.obj", "skybox"));
    meshList.push(meshLoader.load("C:\\EngPathReq\\might_beeeeeeeeeeee\\models\\quad.obj", "quad"));
    meshList.push(meshLoader.load("C:\\EngPathReq\\might_beeeeeeeeeeee\\models\\sphere.obj", "sphere"));

    skeletonList.push(skeletizer.skeletize(*meshList.getByName("loaded"),
                                           "C:\\EngPathReq\\might_beeeeeeeeeeee\\models\\Character_A1016A457\\skeleton.skl"));

    shaders.pushNew("C:\\EngPathReq\\might_beeeeeeeeeeee\\shaders\\obj_vertex.vsh",
                    "C:\\EngPathReq\\might_beeeeeeeeeeee\\shaders\\obj_fragment.fsh", "default");
    shaders.pushNew("C:\\EngPathReq\\might_beeeeeeeeeeee\\shaders\\skybox_vertex.vsh",
                    "C:\\EngPathReq\\might_beeeeeeeeeeee\\shaders\\skybox_fragment.fsh", "skybox");
    shaders.pushNew("C:\\EngPathReq\\might_beeeeeeeeeeee\\shaders\\screen_vertex.vsh",
                    "C:\\EngPathReq\\might_beeeeeeeeeeee\\shaders\\screen_fragment.fsh", "screen");
    shaders.pushNew("C:\\EngPathReq\\might_beeeeeeeeeeee\\shaders\\skeleton_obj_vertex.vsh",
                    "C:\\EngPathReq\\might_beeeeeeeeeeee\\shaders\\skeleton_obj_fragment.fsh", "skeleton");

    tex.loadNew("C://EngPathReq//might_beeeeeeeeeeee//models//Character_A1016A457//1e1868e0.png");//0
    tex.loadNew("C://EngPathReq//might_beeeeeeeeeeee//models//Character_A1016A457//Amiku1.png");//1
    tex.loadNew("C://EngPathReq//might_beeeeeeeeeeee//models//Character_A1016A457//Amiku2.png");//2
    tex.loadNew("C://EngPathReq//might_beeeeeeeeeeee//models//Character_A1016A457//Amiku3.png");//3
    tex.loadNew("C://EngPathReq//might_beeeeeeeeeeee//models//Character_A1016A457//Amiku4.png");//4
    tex.loadNew("C://EngPathReq//might_beeeeeeeeeeee//models//Character_A1016A457//Amiku6.png");//5
    tex.loadNew("C://EngPathReq//might_beeeeeeeeeeee//models//Character_A1016A457//M1.png");//6
    tex.loadNew("C://EngPathReq//might_beeeeeeeeeeee//models//Character_A1016A457//a1.png");//7
    tex.loadNew("C://EngPathReq//might_beeeeeeeeeeee//models//Character_A1016A457//a3.png");//8
    tex.loadNew("C://EngPathReq//might_beeeeeeeeeeee//models//Character_A1016A457//a4.png");//9
    tex.loadNew("C://EngPathReq//might_beeeeeeeeeeee//models//Character_A1016A457//a9.png");//10

    tex.addLayouts(13);
    tex.appendTextureToLayout(0, 0, 0, "texture0");//body
    tex.appendTextureToLayout(1, 0, 6, "texture0");//legs
    tex.appendTextureToLayout(2, 0, 4, "texture0");//обводка

    tex.appendTextureToLayout(3, 0, 1, "texture0");//лицо
    tex.appendTextureToLayout(4, 0, 1, "texture0");//белок
    tex.appendTextureToLayout(5, 0, 1, "texture0");//зрачки
    tex.appendTextureToLayout(6, 0, 1, "texture0");//блёстки
    tex.appendTextureToLayout(7, 0, 2, "texture0");//волосы передние
    tex.appendTextureToLayout(8, 0, 2, "texture0");//волосы передние снизу
    tex.appendTextureToLayout(9, 0, 2, "texture0");//?
    tex.appendTextureToLayout(10, 0, 3, "texture0");//наушники
    tex.appendTextureToLayout(11, 0, 3, "texture0");//наушники - обводка

    tex.appendTextureToLayout(12, 0, 2, "texture0");//tails

    Buffer buffer1(*meshList.getByName("loaded"), *shaders.getByName("default"));
    Buffer skyboxCube(*meshList.getByName("skybox"), *shaders.getByName("skybox"));
    Buffer quad(*meshList.getByName("quad"), *shaders.getByName("screen"));
    Buffer sphere(*meshList.getByName("sphere"), *shaders.getByName("default"));

    SkeletonBuffer model(*skeletonList.getByName("loaded"), *shaders.getByName("skeleton"));

    Material* mat = new Material;
    mat->setAmbientColor(0.01f,0.01f,0.01f);
    mat->setSpecularHighlights(300);

    materials.push(*mat);

    Framebuffer framebuffer(window_width, window_height);
    framebuffer.genTextureColorBuffers(2);
    renderer.addFramebuffer(framebuffer);

    renderer.addNewLightSource(0,0,2,"default");

    renderer.addNewObject(*framebuffer.textureColorBuffers, quad, &materials, "screen");
    renderer.getObjectByName("screen")->rotate(0,180,0);

    renderer.addNewObject(tex, sphere, &materials, "sphere");
    renderer.getObjectByName("sphere")->scaleTo(0.01,0.01,0.01);

    renderer.addNewSkeletonObject(tex, model, &materials, "model");
    renderer.getSkeletonObjectByIndex(0)->setAnimation("C:\\EngPathReq\\might_beeeeeeeeeeee\\models\\Character_A1016A457\\animation.anm", 3);
//    renderer.getSkeletonObjectByIndex(0)->startAnimation();

    vector<string> skyboxSides;
    skyboxSides.push_back("C:\\EngPathReq\\might_beeeeeeeeeeee\\skybox\\right.jpg");
    skyboxSides.push_back("C:\\EngPathReq\\might_beeeeeeeeeeee\\skybox\\left.jpg");
    skyboxSides.push_back("C:\\EngPathReq\\might_beeeeeeeeeeee\\skybox\\top.jpg");
    skyboxSides.push_back("C:\\EngPathReq\\might_beeeeeeeeeeee\\skybox\\bottom.jpg");
    skyboxSides.push_back("C:\\EngPathReq\\might_beeeeeeeeeeee\\skybox\\front.jpg");
    skyboxSides.push_back("C:\\EngPathReq\\might_beeeeeeeeeeee\\skybox\\back.jpg");

    renderer.addNewSkybox(skyboxSides, skyboxCube);
    renderer.getSkyboxObjectByIndex(0)->scaleTo(10,10,10);

    renderer.setBackgroundColor(0.5f, 0.f, 0.f, 0.99f);
    renderer.render(drawFrame);
    return 0;
}
