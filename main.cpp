#include "set.hpp"
#include <iostream>

/**
  @brief Funtore di uguaglianza tra interi
*/
struct equal_int
{
  bool operator()(int a, int b) const
  {
    return a==b;
  }
};

/**
  @brief Funtore di uguaglianza tra stringhe
*/
struct equal_string
{
  bool operator()(std::string a, std::string b) const
  {
    return a==b;
  }
};

/**
  @brief Funtore di parita' di un numero
*/
struct is_even
{
  bool operator()(int a) const
  {
    return a%2 == 0;
  }
};

/**
  @brief Funtore che verifica se un numero e' maggiore di 7
*/
struct greater_than_7
{
  bool operator()(int a) const
  {
    return a > 7;
  }
};

class dipinto
{
  std::string _scuola;
  std::string _autore;
  std::string _titolo;
  std::string _data;
  std::string _sala;

  public:

  dipinto() :_scuola(""), _autore(""), _titolo(""), _data(""), _sala("") {}

  ~dipinto() {}

  dipinto(std::string scuola, std::string autore, std::string titolo, std::string data, std::string sala) :_scuola(scuola),_autore(autore),_titolo(titolo),_data(data),_sala(sala) {}

  std::string get_scuola() const {return _scuola;}
  std::string get_autore() const {return _autore;}
  std::string get_titolo() const {return _titolo;}
  std::string get_data() const {return _data;}
  std::string get_sala() const {return _sala;}
  
  struct equal_dipinto
  {
    bool operator()(const dipinto &d1, const dipinto &d2) const
    {
      if(d1._autore==d2._autore && d1._data==d2._data && d1._sala==d2._sala && d1._scuola==d2._scuola && d1._titolo==d2._titolo)
        return true;
      else
        return false;
    }
  };

  friend std::ostream& operator<<(std::ostream &os, const dipinto &d)
  {
      os<<d._scuola<<", "<<d._autore<<", "<<d._titolo<<", "<<d._data<<", "<<d._sala;
      return os;
  }

  struct cerca
  {
      std::string chiave, titolo;
      cerca(std::string param): chiave(param){}

      bool operator()(dipinto d)
      {
          titolo = d.get_titolo();
          if(titolo.find(chiave) != std::string::npos)
            return true;
          else
            return false;
      }
  };
};

void sep()
{
  std::cout<< std::endl<<"--------------------------------------------------------------------------"<< std::endl<< std::endl;
}

void interi()
{
  set<int, equal_int> s;

  std::cout << "Test int: " << std::endl << std::endl;

  std::cout << "(add 1) -> " << s.add(1) << std::endl;
  std::cout << "(add 2) -> " << s.add(2) << std::endl;
  std::cout << "(add 3) -> " << s.add(3) << std::endl;

  std::cout << "(contains 1) -> " << s.contains(1) << std::endl;
  std::cout << "(contains 2) -> " << s.contains(2) << std::endl;
  std::cout << "(contains -1) -> " << s.contains(-1) << std::endl;

  std::cout << std::endl << "Print set: " <<s<< std::endl << std::endl;

  std::cout << "(add 4) -> " << s.add(4) << std::endl;
  std::cout << "(add 5) -> " << s.add(5) << std::endl;

  std::cout << std::endl << "Print set: " <<s<< std::endl << std::endl;

  std::cout << "(remove 1) -> " << s.remove(1) << std::endl;
  std::cout << "(remove 2) -> " << s.remove(2) << std::endl;
  std::cout << "(remove 3) -> " << s.remove(3) << std::endl;

  std::cout << std::endl << "Print set: " <<s<< std::endl << std::endl;

  std::cout << "(print set[0]) -> " << s[0] << std::endl;
  std::cout << "(print set[1]) -> " << s[1] << std::endl;
}

void stringhe()
{
  set<std::string, equal_string> s;

  std::cout << "Test std::string: " << std::endl << std::endl;

  std::cout << "(add str1) -> " << s.add("str1") << std::endl;
  std::cout << "(add str2) -> " << s.add("str2") << std::endl;
  std::cout << "(add str3) -> " << s.add("str3") << std::endl;
  
  std::cout << "(contains str1) -> " << s.contains("str1") << std::endl;
  std::cout << "(contains str2) -> " << s.contains("str2") << std::endl;
  std::cout << "(contains str-1) -> " << s.contains("str-1") << std::endl;

  std::cout << std::endl << "Print set: " <<s<< std::endl << std::endl;

  std::cout << "(add str4) -> " << s.add("str4") << std::endl;
  std::cout << "(add str5) -> " << s.add("str5") << std::endl;

  std::cout << std::endl << "Print set: " <<s<< std::endl << std::endl;

  std::cout << "(remove str1) -> " << s.remove("str1") << std::endl;
  std::cout << "(remove str2) -> " << s.remove("str2") << std::endl;
  std::cout << "(remove str3) -> " << s.remove("str3") << std::endl;

  std::cout << std::endl << "Print set: " <<s<< std::endl << std::endl;

  std::cout << "(print set[0]) -> " << s[0] << std::endl;
  std::cout << "(print set[1]) -> " << s[1] << std::endl;
}

void classe()
{
  set<dipinto, dipinto::equal_dipinto> s;

  std::cout << "Test classe: " << std::endl << std::endl;

  dipinto dipinto1("d1", "d1", "d1", "d1", "d1");
  dipinto dipinto2("d2", "d2", "d2", "d2", "d2");
  dipinto dipinto3("d3", "d3", "d3", "d3", "d3");
  dipinto dipinto100;

  std::cout << "(add dipinto1) -> " << s.add(dipinto1) << std::endl;
  std::cout << "(add dipinto2) -> " << s.add(dipinto2) << std::endl;
  
  std::cout << "(contains dipinto1) -> " << s.contains(dipinto1) << std::endl;
  std::cout << "(contains dipinto2) -> " << s.contains(dipinto2) << std::endl;
  std::cout << "(contains dipinto100) -> " << s.contains(dipinto100) << std::endl;

  std::cout << std::endl << "Print set: " <<s<< std::endl << std::endl;

  std::cout << "(add dipinto3) -> " << s.add(dipinto3) << std::endl;

  std::cout << std::endl << "Print set: " <<s<< std::endl << std::endl;

  std::cout << "(remove dipinto1) -> " << s.remove(dipinto1) << std::endl;

  std::cout << std::endl << "Print set: " <<s<< std::endl << std::endl;

  std::cout << "(print set[0]) -> " << s[0] << std::endl;
  std::cout << "(print set[1]) -> " << s[1] << std::endl;
}

void operatori_primitivi()
{
  std::cout << "Test operatori +/- e filter_out: " << std::endl << std::endl;

  set<int, equal_int> s1;
  set<int, equal_int> s2;

  s1.add(1);
  s1.add(2);
  s1.add(3);
  s1.add(4);
  s1.add(10);

  s2.add(5);
  s2.add(6);
  s2.add(7);
  s2.add(8);
  s2.add(10);

  std::cout << std::endl << "Print set 1: " <<s1<< std::endl;
  std::cout << std::endl << "Print set 2: " <<s2<< std::endl << std::endl;

  std::cout << "Operator+ : " << (s1+s2) << std::endl;
  std::cout << "Operator- : " << (s1-s2) << std::endl;
  std::cout << "filter_out set 1, numeri > 7 : " << filter_out(s1, greater_than_7()) << std::endl;
  std::cout << "filter_out set 2, numeri pari : " << filter_out(s2, is_even()) << std::endl;

  std::cout << std::endl << "Svuotamento set 1 " << std::endl;
  s1.remove(1);
  s1.remove(2);
  s1.remove(3);
  s1.remove(4);
  s1.remove(10);

  std::cout << std::endl << "Print set 1: " <<s1<< std::endl;
  std::cout << std::endl << "Print set 2: " <<s2<< std::endl << std::endl;

  std::cout << "Operator+ : " << (s1+s2) << std::endl;
  std::cout << "Operator- : " << (s1-s2) << std::endl;
}

void operatori_complessi()
{
  std::cout << "Test operatori +/- e filter_out su tipi complessi: " << std::endl << std::endl;

  set<dipinto, dipinto::equal_dipinto> s1;
  set<dipinto, dipinto::equal_dipinto> s2;

  dipinto dipinto1("d1", "d1", "d1", "d1", "d1");
  dipinto dipinto2("d2", "d2", "d2", "d2", "d2");
  dipinto dipinto3("d3", "d3", "d3", "d3", "d3");
  dipinto dipinto4("d4", "d4", "d4", "d4", "d4");
  dipinto dipinto9("d9", "d9", "d9", "d9", "d9");
  

  s1.add(dipinto1);
  s1.add(dipinto2);
  s1.add(dipinto9);

  s2.add(dipinto3);
  s2.add(dipinto4);
  s2.add(dipinto9);

  std::cout << std::endl << "Print set 1: " <<s1<< std::endl;
  std::cout << std::endl << "Print set 2: " <<s2<< std::endl << std::endl;

  std::cout << "Operator+ : " << (s1+s2) << std::endl;
  std::cout << "Operator- : " << (s1-s2) << std::endl;
  std::cout << "filter_out set 1, se titolo(3^ variabile) contiene d : " << filter_out(s1, dipinto::cerca("d")) << std::endl;
  std::cout << "filter_out set 2, se titolo(3^ variabile) contiene 10 : " << filter_out(s2, dipinto::cerca("10")) << std::endl;

  s1.empty();
  std::cout << std::endl << "Svuotamento set 1: " <<s1<< std::endl;

  std::cout << std::endl << "Print set 1: " <<s1<< std::endl;
  std::cout << std::endl << "Print set 2: " <<s2<< std::endl << std::endl;

  std::cout << "Operator+ : " << (s1+s2) << std::endl;
  std::cout << "Operator- : " << (s1-s2) << std::endl;
}

void file()
{
  std::cout << "Test stampa std::string su file: " << std::endl << std::endl;

  set<std::string, equal_string> s;

  s.add("s1");
  s.add("s2");
  s.add("s3");
  s.add("s4");
  s.add("s5");
  s.add("s6");
  s.add("s7");
  s.add("s8");
  s.add("s9");
  s.add("s0");

  std::cout << std::endl << "Print set: " <<s<< std::endl << std::endl;

  save(s, "prova.txt");

  std::cout << std::endl << "Set salvato su \"prova.txt\" " << std::endl;
}

void iteratori_primitivi()
{
  std::cout << "Test iteratori primitivi:" << std::endl << std::endl;

  set<std::string, equal_string> s;

  set<std::string, equal_string>::const_iterator ib, ie;

  s.add("s1");
  s.add("s2");
  s.add("s3");
  s.add("s4");
  s.add("s5");
  s.add("s6");
  s.add("s7");
  s.add("s8");
  s.add("s9");
  s.add("s0");

  std::cout << "Stampa set di stringhe tramite iteratore: " << std::endl;
  for(ib=s.begin(), ie=s.end();ib!=ie;ib++)
  {
    std::cout << *ib << std::endl;
  }
}

void iteratori_composti()
{
  std::cout << "Test iteratori composti: " << std::endl << std::endl;

  set<dipinto, dipinto::equal_dipinto> s;

  set<dipinto, dipinto::equal_dipinto>::const_iterator ib, ie;

  dipinto dipinto1("d1", "d1", "d1", "d1", "d1");
  dipinto dipinto2("d2", "d2", "d2", "d2", "d2");
  dipinto dipinto3("d3", "d3", "d3", "d3", "d3");
  dipinto dipinto4("d4", "d4", "d4", "d4", "d4");
  dipinto dipinto5("d5", "d5", "d5", "d5", "d5");

  s.add(dipinto1);
  s.add(dipinto2);
  s.add(dipinto3);
  s.add(dipinto4);
  s.add(dipinto5);

  std::cout << "Stampa set di dipinti tramite iteratore: " << std::endl;
  for(ib=s.begin(), ie=s.end();ib!=ie;ib++)
  {
    std::cout << *ib << std::endl;
  }
}

int main()
{
  sep();
  interi();
  sep();
  stringhe();
  sep();
  classe();
  sep();
  operatori_primitivi();
  sep();
  operatori_complessi();
  sep();
  file();
  sep();
  iteratori_primitivi();
  sep();
  iteratori_composti();
  sep();

  return 0;
}
