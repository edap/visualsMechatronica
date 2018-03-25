import qbs
import qbs.Process
import qbs.File
import qbs.FileInfo
import qbs.TextFile
import "../../../libs/openFrameworksCompiled/project/qtcreator/ofApp.qbs" as ofApp

Project{
    property string of_root: '../../..'

    ofApp {
        name: { return FileInfo.baseName(sourceDirectory) }

        files: [
            "bin/data/shaders_gl3/libs/mercury.glsl",
            "bin/data/shaders_gl3/passthruogh.vert",
            "bin/data/shaders_gl3/raymarching/bend_five_rings.frag",
            "bin/data/shaders_gl3/raymarching/blending_boh.frag",
            "bin/data/shaders_gl3/raymarching/blending_rings.frag",
            "bin/data/shaders_gl3/raymarching/blobby.frag",
            "bin/data/shaders_gl3/raymarching/blobby_old_light.frag",
            "bin/data/shaders_gl3/raymarching/cup.frag",
            "bin/data/shaders_gl3/raymarching/inside_rings.frag",
            "bin/data/shaders_gl3/raymarching/mercury_models.frag",
            "bin/data/shaders_gl3/raymarching/multimaterial.frag",
            "bin/data/shaders_gl3/raymarching/multistructure.frag",
            "bin/data/shaders_gl3/raymarching/multistructure1.frag",
            "bin/data/shaders_gl3/raymarching/multistructure2.frag",
            "bin/data/shaders_gl3/raymarching/multistructure3.frag",
            "bin/data/shaders_gl3/raymarching/two_spheres.frag",
            "src/Layer.h",
            "src/Recorder.cpp",
            "src/Recorder.h",
            "src/Scenes.h",
            "src/context/AppTime.cpp",
            "src/context/AppTime.h",
            "src/context/AudioAnalysis.cpp",
            "src/context/AudioAnalysis.h",
            "src/context/Panel.cpp",
            "src/context/Panel.h",
            "src/layers/Blobby.cpp",
            "src/layers/Blobby.h",
            "src/layers/Cup.cpp",
            "src/layers/Cup.h",
            "src/layers/Deformed1.cpp",
            "src/layers/Deformed1.h",
            "src/layers/Deformed2.cpp",
            "src/layers/Deformed2.h",
            "src/layers/Deformed3.cpp",
            "src/layers/Deformed3.h",
            "src/layers/MercuryModels.cpp",
            "src/layers/MercuryModels.h",
            "src/layers/Multistructure.cpp",
            "src/layers/Multistructure.h",
            "src/layers/Multistructure1.cpp",
            "src/layers/Multistructure1.h",
            "src/layers/Multistructure2.cpp",
            "src/layers/Multistructure2.h",
            "src/layers/Multistructure3.cpp",
            "src/layers/Multistructure3.h",
            "src/layers/PlotOctave.cpp",
            "src/layers/PlotOctave.h",
            "src/layers/RayMarchRings.cpp",
            "src/layers/RayMarchRings.h",
            "src/layers/RotatingSpheres.cpp",
            "src/layers/RotatingSpheres.h",
            "src/layers/templates/SimpleFragment.cpp",
            "src/layers/templates/SimpleFragment.h",
            "src/scenes/DebugFFT.cpp",
            "src/scenes/DebugFFT.h",
            "src/scenes/MercurySketch.cpp",
            "src/scenes/MercurySketch.h",
            "src/scenes/Scene0.cpp",
            "src/scenes/Scene0.h",
            "src/main.cpp",
            "src/ofApp.cpp",
            "src/ofApp.h",
            "src/scenes/Scene1.cpp",
            "src/scenes/Scene1.h",
            "src/scenes/Scene10.cpp",
            "src/scenes/Scene10.h",
            "src/scenes/Scene2.cpp",
            "src/scenes/Scene2.h",
            "src/scenes/Scene3.cpp",
            "src/scenes/Scene3.h",
            "src/scenes/Scene4.cpp",
            "src/scenes/Scene4.h",
            "src/scenes/Scene5.cpp",
            "src/scenes/Scene5.h",
            "src/scenes/Scene6.cpp",
            "src/scenes/Scene6.h",
            "src/scenes/Scene7.cpp",
            "src/scenes/Scene7.h",
            "src/scenes/Scene8.cpp",
            "src/scenes/Scene8.h",
            "src/scenes/Scene9.cpp",
            "src/scenes/Scene9.h",
        ]

        of.addons: [
            'ofxAssimpModelLoader',
            'ofxGui',
            'ofxLayer',
            'ofxMaxim',
            'ofxAutoReloadedShader',
            'ofxAnimationPrimitives',
            'ofxGlobalContext',
            'ofxVideoRecorder'
        ]

        // additional flags for the project. the of module sets some
        // flags by default to add the core libraries, search paths...
        // this flags can be augmented through the following properties:
        of.pkgConfigs: []       // list of additional system pkgs to include
        of.includePaths: []     // include search paths
        of.cFlags: []           // flags passed to the c compiler
        of.cxxFlags: []         // flags passed to the c++ compiler
        of.linkerFlags: []      // flags passed to the linker
        of.defines: []          // defines are passed as -D to the compiler
        // and can be checked with #ifdef or #if in the code
        of.frameworks: []       // osx only, additional frameworks to link with the project
        of.staticLibraries: []  // static libraries
        of.dynamicLibraries: [] // dynamic libraries

        // other flags can be set through the cpp module: http://doc.qt.io/qbs/cpp-module.html
        // eg: this will enable ccache when compiling
        //
        // cpp.compilerWrapper: 'ccache'

        Depends{
            name: "cpp"
        }

        // common rules that parse the include search paths, core libraries...
        Depends{
            name: "of"
        }

        // dependency with the OF library
        Depends{
            name: "openFrameworks"
        }
    }

    property bool makeOF: true  // use makfiles to compile the OF library
    // will compile OF only once for all your projects
    // otherwise compiled per project with qbs

    references: [FileInfo.joinPaths(of_root, "/libs/openFrameworksCompiled/project/qtcreator/openFrameworks.qbs")]
}
