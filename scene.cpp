#include "scene.h"
#include "qdebug.h"
void Scene::setSystem_on(bool value)
{
    system_on = value;
}

bool Scene::getSystem_on() const
{
    return system_on;
}

void Scene::addMap(const QString &file_name) //добавляет и рисует карту на сцену
{
    map.loadMapFromFile(file_name);
    for(int counter_y = 0; (unsigned int)counter_y < map.getArray_y(); counter_y++)
        for(int counter_x = 0; (unsigned int)counter_x < map.getArray_x(); counter_x++)
            addItem(&map.getMap_ptr()[counter_x + counter_y*map.getArray_x()]);
}
void Scene::addTrafficLights() //добавляет светофоры на сцену
{
    TrafficLight *traffic_lights_map[map.getArray_x() + map.getArray_x()*map.getArray_y()];
    std::vector<TrafficLight*> traffic_lights;
    TrafficLight lights(map);
    TrafficLightGroup *group;
    TLControl* controler;
    lights.searchCrossroad();    //поиск перекрёстков
    lights.setFullBlock();
    auto traffic_light_ptr = lights.getTrafficLightVector();    //запись светофоров в контейнер traffic_light_ptr

    for(unsigned int a = 0; a < lights.getContainerSize(); ++a)
    {
        int x = static_cast<int>(traffic_light_ptr[a].pos().rx())/PIXMAP_SIZE;
        int y = static_cast<int>(traffic_light_ptr[a].pos().ry())/PIXMAP_SIZE;
        addItem(&traffic_light_ptr[a]); //добавление светофоров на карту
        traffic_lights_map[x + y*map.getArray_x()] = &traffic_light_ptr[a];
        traffic_lights.emplace_back(&traffic_light_ptr[a]);
    }
    // разбитие сфетофоров на группки
    for(auto obj : traffic_lights){
        if(!obj->isInGroup()){
            group = new TrafficLightGroup(&map);
            group->joinTL(obj, traffic_lights_map);
            controler = new TLControl(*group);
            controler->createNet();
            traffic_lights_group.emplace_back(group);
            controlers.emplace_back(controler);
        }
    }
}
void Scene::addCar()
{
    car_centers.searchCenterPoint(&map);
    auto car = &car_centers.addNewCar(&map);
    if(car != nullptr)
        addItem(car);
}

unsigned int Scene::getCarNumber() const{
    return car_centers.getCarNumber();
}

void Scene::renewTLStatus(){
    if(system_on){
        for(auto obj : controlers){
            obj->calculate();
            obj->setStatus();
        }
    }else{
        for(auto obj : traffic_lights_group)
            obj->renewTLStatus();
    }
}

Scene::~Scene()
{
    for(auto obj : controlers)
        delete obj;
    for(auto obj : traffic_lights_group)
        delete obj;
}
