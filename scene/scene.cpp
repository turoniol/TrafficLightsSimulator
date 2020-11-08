#include "scene.h"
#include "qdebug.h"

Scene::Scene()
{
  carSpawnTimer = new QTimer(this);
  trafficLightsTimer = new QTimer(this);

  int spawnTime  = 100;
  int renewTLColorTime = 200;

  carSpawnTimer->start(spawnTime);
  trafficLightsTimer->start(renewTLColorTime);

  // car adding
  connect(carSpawnTimer, &QTimer::timeout, [this](){
      addCar();
    });
  // traffic lights control
  connect(trafficLightsTimer, &QTimer::timeout, [this](){
      renewTLStatus();
  });
}
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
  int array_x = map.getArray_x();
  int array_y = map.getArray_y();
  int graphicsWidth = array_x * PIXMAP_SIZE;
  int graphicsHeight = array_y * PIXMAP_SIZE;

  for (int counter_y = 0; counter_y < array_y; counter_y++)
    for (int counter_x = 0; counter_x < array_x; counter_x++)
      addItem(&map.getMap_ptr()[counter_x + counter_y*map.getArray_x()]);

  setSceneRect(0, 0, graphicsWidth, graphicsHeight);
}
void Scene::addTrafficLights() //добавляет светофоры на сцену
{
  TrafficLight *traffic_lights_map[map.getArray_x() + map.getArray_x()*map.getArray_y()];
  std::vector<TrafficLight*> traffic_lights;
  TrafficLight lights(map);
  TrafficLightGroup *group = nullptr;
  TLControl* controler = nullptr;
  lights.searchCrossroad();    //поиск перекрёстков
  lights.setFullBlock();
  auto traffic_light_ptr = lights.getTrafficLightVector();    //запись светофоров в контейнер traffic_light_ptr

  for(unsigned int a = 0; a < lights.getContainerSize(); ++a)
    {
      int x = (int)(traffic_light_ptr[a].pos().rx()) / PIXMAP_SIZE;
      int y = (int)(traffic_light_ptr[a].pos().ry()) / PIXMAP_SIZE;
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

void Scene::renewTLStatus(){
  if (system_on){
      for (auto obj : controlers){
          obj->calculate();
          obj->setStatus();
        }
    }
  else
    {
      for(auto obj : traffic_lights_group)
        obj->renewTLStatus();
    }
}

void Scene::addCar()
{
  car_centers.searchCenterPoint(&map);
      auto car = &car_centers.addNewCar(&map);
      if (car != nullptr)
        addItem(car);
}

Scene::~Scene()
{
  delete trafficLightsTimer;
  delete carSpawnTimer;
  for(auto obj : controlers)
    delete obj;
  for(auto obj : traffic_lights_group)
    delete obj;
}
