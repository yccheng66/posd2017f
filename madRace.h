#ifndef MADRACE_H
#define MADRACE_H

class MadCar {
public:
  MadCar (int iniSpeed): _speed(iniSpeed){}
  int speed() const {return _speed;}
  void boom(int incSpeed) {_speed+=incSpeed;}
private:
  int _speed;
};

class MadBike {
public:
  MadBike (int iniSpeed, int inc, int maxSpeed): _speed(iniSpeed), _inc(inc), _maxSpeed(maxSpeed){}
  int speed() const {return _speed;}
  void boom() {
    if (_speed +_inc >= _maxSpeed)
      throw std::string("MadBike speeding");
    else
      _speed += _inc;
  }
private:
  int _speed;
  int _inc;
  int _maxSpeed;
};

#endif
