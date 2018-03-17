## context
In this folder there are the classes that are shared among the whole application. All the context inherits from `ofxGlobalContext`

## scenes
It is possible to make different scenes and to fade them in and out using ofxAnimationPrimitives.
Each scene is composed by a Layers Manager (from ofxLayer). Each layer manager can have multiple layers, and can blend them together or just draw one of them.

When initializing a scene, you can pass arguments to it. Example:

```cpp
class DebugFFT : public ofxAnimationPrimitives::Scene{
public:
    OFX_ANIMATION_PRIMITIVES_DEFINE_SCENE(DebugFFT);
    DebugFFT(const int arg0);
    void update(); 
    // ...
};
```

## level manager

## layers
Here you load the asset that you need

## credits
This structure and the usage of `ofxLayer`, `ofxAnimationPrimitives` and `ofxGlobalContext` comes from [Yuma Taesu, Live](https://github.com/yumataesu/Live).
