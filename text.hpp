#ifndef TEXT_TEXT_H
#define TEXT_TEXT_H

#define textheight 15

class Text {
  private:

    public:
    int row[30];

  Text(int text[30]) {

    for (int i = 0; i < 30; i++) {
      this -> row[i] = text[i];
    }

  }
  

};

#endif