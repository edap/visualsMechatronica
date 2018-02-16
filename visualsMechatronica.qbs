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
            "bin/data/shaders_gl3/march1.frag",
            "bin/data/shaders_gl3/passthruogh.vert",
            "src/Layer.h",
            "src/Scenes.h",
            "src/context/AppTime.cpp",
            "src/context/AppTime.h",
            "src/context/AudioAnalysis.cpp",
            "src/context/AudioAnalysis.h",
            "src/fftPlotter.cpp",
            "src/fftPlotter.h",
            "src/layers/PlotOctave.cpp",
            "src/layers/PlotOctave.h",
            "src/layers/RayMarchRings.cpp",
            "src/layers/RayMarchRings.h",
            "src/scenes/DebugFFT.cpp",
            "src/scenes/DebugFFT.h",
            "src/scenes/Scene0.cpp",
            "src/scenes/Scene0.h",
            "src/main.cpp",
            "src/ofApp.cpp",
            "src/ofApp.h",
        ]

        of.addons: [
            'ofxAssimpModelLoader',
            'ofxGui',
            'ofxLayer',
            'ofxMaxim',
            'ofxAutoReloadedShader',
            'ofxAnimationPrimitives',
            'ofxGlobalContext'
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
