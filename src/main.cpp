#include <algorithm>
#include <cmath>
#include <iostream>
#include <map>
#include <utility>
#include <vector>

using namespace std;

// const int INF = 1e5 + 2, MOD = 1e7 + 7;

/*
constraints:
enemies<=10000
comrads<=10000
*/

struct comrad;
struct enemy;

struct comrad {
  long double x, y, z;
  long double range;
  int role;
  bool isAvailable;
  long long id;
  vector<long long> targets;
};

struct enemy {
  long double x, y, z;
  long long id;
  bool isAvailable;
  vector<long long> targetedBy;
};

string role[3] = {"attack", "surveillance", "defence"};

class Calculator {
public:
  long double comradEnemyDis(comrad a, enemy b) {
    long double myDistance =
        sqrt(pow(a.x - b.x, 2.0) + pow(a.y - b.y, 2.0) + pow(a.z - b.z, 2.0));
    return myDistance;
  }
};

class Radar {
public:
  vector<comrad> comrads;
  vector<enemy> enemies;

  Radar() {}
  Radar(vector<comrad> &_comrads) { comrads = _comrads; }
  Radar(vector<enemy> &_enemies) { enemies = _enemies; }
  Radar(vector<comrad> &_comrads, vector<enemy> &_enemies) {
    comrads = _comrads;
    enemies = _enemies;
  }

  void addComrad(comrad newComrad) { comrads.push_back(newComrad); }
  void addEnemy(enemy newEnemy) { enemies.push_back(newEnemy); }
};

class Detector : public Calculator {
protected:
  vector<comrad> comrads;
  vector<enemy> enemies;

public:
  Detector(Radar radar) {
    comrads = radar.comrads;
    enemies = radar.enemies;
    for (int i = 0; i < comrads.size(); i++) {
      for (int j = 0; j < enemies.size(); j++) {
        if (comrads[i].isAvailable) {
          if (comrads[i].range >= comradEnemyDis(comrads[i], enemies[i]) &&
              enemies[i].isAvailable) {
            if (!count(comrads[i].targets.begin(), comrads[i].targets.end(),
                       enemies[i].id)) {
              comrads[i].targets.push_back(enemies[j].id);
            }
            if (!count(enemies[i].targetedBy.begin(),
                       enemies[i].targetedBy.end(), comrads[i].id)) {
              enemies[j].targetedBy.push_back(comrads[i].id);
            }
          }
        }
      }
    }
  }
  void priDec() {
    cout << "--------------------" << endl;
    for (auto i : comrads) {
      for (auto a : i.targets) {
        cout << a << " ";
      }
      cout << i.targets.size() << endl;
    }
    cout << "--------------------" << endl;
    for (auto i : enemies) {
      for (auto a : i.targetedBy) {
        cout << a << " ";
      }
      cout << i.targetedBy.size() << endl;
    }
    cout << comrads[0].targets.size() << endl;
    cout << enemies[0].targetedBy.size() << endl;
  }
};

class Allocator : public Detector {
protected:
  map<long long, vector<pair<long double, long long>>>
      targetMap; // first -> distance, second -> enemy id
  map<long long, vector<pair<long double, long long>>>
      targetedMap; // first -> distance, second -> comrad id

public:
  Allocator(Radar radar) : Detector(radar) {
    for (auto c : comrads) {
      for (auto id : c.targets) {
        targetMap[c.id].push_back(
            make_pair(comradEnemyDis(c, enemies[id]), id));
      }
      sort(targetMap[c.id].begin(), targetMap[c.id].end());
    }
    for (auto e : enemies) {
      for (auto id : e.targetedBy) {
        targetedMap[e.id].push_back(
            make_pair(comradEnemyDis(comrads[id], e), id));
      }
      sort(targetedMap[e.id].begin(), targetedMap[e.id].end());
    }
  }

  void priAll() {
    for (auto t : targetedMap) {
      for (auto i : t.second) {
        cout << i.first << " : " << i.second << endl;
      }
    }
    for (auto t : targetMap) {
      for (auto i : t.second) {
        cout << i.first << " : " << i.second << endl;
      }
    }
  }
};

class Striker : public Allocator {
protected:
  vector<vector<long long>>
      finalTargets; // first -> comrad id, second -> enemy id
public:
  Striker(Radar radar) : Allocator(radar) {
    map<long long, vector<pair<long double, long long>>>::iterator it;
    for (it = targetedMap.begin(); it != targetedMap.end(); it++) {
      if (it->second[0].first != it->second[1].first) {
        finalTargets.push_back({it->second[0].second, it->first});
      } else {
        if (targetMap[it->second[0].second].size() ==
            targetMap[it->second[1].second].size()) {
          if (targetMap[it->second[0].second][0].first <
              targetMap[it->second[1].second][0].first) {
            finalTargets.push_back({it->second[1].second, it->first});
          } else {
            finalTargets.push_back({it->second[0].second, it->first});
          }
        } else if (targetMap[it->second[0].second].size() <
                   targetMap[it->second[1].second].size()) {
          finalTargets.push_back({it->second[0].second, it->first});
        } else {
          finalTargets.push_back({it->second[1].second, it->first});
        }
      }
    }
  }
  void priStr() {
    for (auto i : finalTargets) {
      cout << i[0] << " : " << i[1] << endl;
    }
  }
};

int main() {
//   vector<enemy> es;
//   vector<comrad> cs;
  Radar radar;

  for (int i = 0; i < 10; i++) {
    comrad c;
    c.x = i;
    c.y = i;
    c.z = i;
    c.range = 2 + i;
    c.role = 0;
    c.isAvailable = true;
    c.id = i;
    radar.addComrad(c);
  }

//   cs[0].range = 10;

  for (int i = 0; i < 10; i++) {
    enemy e;
    e.x = i + 1;
    e.y = i + 1;
    e.z = i + 1;
    e.id = i;
    e.isAvailable = true;
    radar.addEnemy(e);
  }


  Striker striker(radar);
  striker.priStr();
  // striker.priAll();
  // striker.priDec();

  return 0;
}