#ifndef SELECTABLE_H
#define SELECTABLE_H
class Selectable {
   public:
      virtual bool getSelected() const = 0;
      virtual void setSelected(bool value) = 0;
   private:
      bool selected;
};
#endif // SELECTABLE_H
