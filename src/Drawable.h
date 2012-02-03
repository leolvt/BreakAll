#ifndef DRAWABLE_H
#define DRAWABLE_H

// ============================================== //

class Drawable {
    public:
        virtual void display() = 0;
        virtual void step() = 0;
};

// ============================================== //

#endif /* DRAWABLE_H */
