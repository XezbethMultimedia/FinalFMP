# FinalFMP
A text based RPG using C++, JSON and Ink Scripting Language
## Week 1
- [x] classes for object in C++
- [x] helper functions to convert JSON
- [x] basic engine outline
- [x] pickup system
- [x] use system
- [-] movement system
- [-] map generator
- [-] save system
- [-] story system
- [-] attacking
### Day 1

```cpp
#include <iostream>
#include <fstream>
#include "json.hpp"

namespace core {
  using json = nlohmann::json;
```
The library `iostream` is for the input and output streams which allow my code to interact with the console via streams.
`fstream` is a library that allows interaction with files via the stream system.
`json.hpp` is a library by nlohmann which allows interaction and implementation of JSON files in C++.
I chose to use - [nlohmann/json.git](https://github.com/nlohmann/json.git) because it is used by Microsoft and other companies that use JSON in C++.

The next part of the program is creating a namespace called `core`, this is so I can organise my code more efficiently.
The part after that is calling the namespace `nlohmann::json` as `json` by using the `using` command, thi is to simplify the code so I do not have to repeat myself multiple times.

After that we get into the first main part of the code, this is creating the base object class in C++ and creating namespaces to store them in to keep it all organised.
The use of a namespace also means I can put helper functions in to help with JSON without confusing the compiler.

```cpp
namespace object {

  class object {
    public:
      std::string name = "object";
      int pos_x = 0;
      int pos_y = 0;
      int siz_x = 0;
      int siz_y = 0;
    };

  void to_json(json& j, const object& o) {
    j = json{
      {"name", o.name},
      {"pos_x", o.pos_x},
      {"pos_y", o.pos_y},
      {"siz_x", o.siz_x},
      {"siz_y", o.siz_y}
    };
  }

  void from_json(const json& j, object& o) {
    j.at("name").get_to(o.name);
    j.at("pos_x").get_to(o.pos_x);
    j.at("pos_y").get_to(o.pos_y);
    j.at("siz_x").get_to(o.siz_x);
    j.at("siz_y").get_to(o.siz_y);
  }
}
```
The function `to_json` maps data values from the class to JSON key pairs so it can be saved within a JSON file.
`from_json` does the same thing but the other way, it maps JSON key pairs to class data values.
The following namespaces do the same thing but adding extra variables for data that is needed within the game, the meaning of these will be explained below.

```cpp
namespace entity {

  class entity : public object::object {
    public:
      int hp = 0;
      int xp = 0;
      int lv = 0;

      int atk = 0;
      int def = 0;
      int dmg = 0;

      void death();
      void lvlup();
  };

  void to_json(json& j, const entity& e) {
    j = json{
      {"name", e.name},
      {"pos_x", e.pos_x},
      {"pos_y", e.pos_y},
      {"siz_x", e.siz_x},
      {"siz_y", e.siz_y},
      {"hp", e.hp},
      {"xp", e.xp},
      {"lv", e.lv},
      {"atk", e.atk},
      {"def", e.def},
      {"dmg", e.dmg},
    };
  }

  void from_json(const json& j, entity& e) {
    j.at("name").get_to(e.name);
    j.at("pos_x").get_to(e.pos_x);
    j.at("pos_y").get_to(e.pos_y);
    j.at("siz_x").get_to(e.siz_x);
    j.at("siz_y").get_to(e.siz_y);

    j.at("hp").get_to(e.hp);
    j.at("xp").get_to(e.xp);
    j.at("lv").get_to(e.lv);

    j.at("atk").get_to(e.atk);
    j.at("def").get_to(e.def);
    j.at("dmg").get_to(e.dmg);
  }
}

namespace item {

  class item : public object::object {
    public:
      int* stat = NULL;
      int value = 0;
    };

  void to_json(json& j, const item& i) {
    j = json{
      {"name", i.name},
      {"pos_x", i.pos_x},
      {"pos_y", i.pos_y},
      {"siz_x", i.siz_x},
      {"siz_y", i.siz_y},
      {"stat", *i.stat},
      {"value", i.value}
    };
  }

  void from_json(const json& j, item& i) {
    j.at("name").get_to(i.name);
    j.at("pos_x").get_to(i.pos_x);
    j.at("pos_y").get_to(i.pos_y);
    j.at("siz_x").get_to(i.siz_x);
    j.at("siz_y").get_to(i.siz_y);
    j.at("stat").get_to(*i.stat);
    j.at("value").get_to(i.value);
  }
}
```
|`object`| |
|--------|-|
|`std::string name`|name of the object|
|`int pos_x`|x position of the object|
|`int pos_y`|y position of the object|
|`int siz_x`|width of the object|
|`int siz_y`|depth of the object|

|`entity`|inherits from `object`|
|--------|----------------------|
|`int hp`|health points of the entity|
|`int xp`|experience points of the entity|
|`int lv`|level of the entity|
|`int atk`|attack strength of the entity|
|`int def`|defence strength of the entity|
|`int dmg`|damage amount of the entity|

|`item`|inherits from `object`|
|------|----------------------|
|`int* stat`|pointer to the stat that will change|
|`int value`|the amount the intem will change that stat|
