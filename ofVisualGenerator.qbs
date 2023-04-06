import qbs
import qbs.Process
import qbs.File
import qbs.FileInfo
import qbs.TextFile
import "../../../libs/openFrameworksCompiled/project/qtcreator/ofApp.qbs" as ofApp

Project{
    property string of_root: '../../..'

    ofApp {
        name: { return FileInfo.baseName(path) }

        files: [
            'src/CircleGrow.cpp',
            'src/CircleGrow.h',
            'src/MainMixer.cpp',
            'src/MainMixer.h',
            'src/ManagerLayer.cpp',
            'src/ManagerLayer.h',
            'src/Overlay.h',
            'src/ParticleGrowTexture.cpp',
            'src/ParticleGrowTexture.h',
            'src/ParticleSystem.cpp',
            'src/ParticleSystem.h',
            'src/ParticleSystemTexture.cpp',
            'src/ParticleSystemTexture.h',
            'src/PreviewApp.cpp',
            'src/PreviewApp.h',
            'src/SimpleDots.cpp',
            'src/SimpleDots.h',
            'src/SimpleStripes.cpp',
            'src/SimpleStripes.h',
            'src/SongBeamer.cpp',
            'src/SongBeamer.h',
            'src/SoundAnalyzer.cpp',
            'src/SoundAnalyzer.h',
            'src/SpectrumVisu.cpp',
            'src/SpectrumVisu.h',
            'src/SphereGrow.cpp',
            'src/SphereGrow.h',
            'src/StripeCubes.cpp',
            'src/StripeCubes.h',
            'src/StripeSpiral.cpp',
            'src/StripeSpiral.h',
            'src/TextureGen.h',
            'src/VjObject.cpp',
            'src/VjObject.h',
            'src/WaveMeshAdvTex.cpp',
            'src/WaveMeshAdvTex.h',
            'src/WaveMeshOverlay.cpp',
            'src/WaveMeshOverlay.h',
            'src/WaveMeshTexture.cpp',
            'src/WaveMeshTexture.h',
            'src/kiss/_kiss_fft_guts.h',
            'src/kiss/kiss_fft.c',
            'src/kiss/kiss_fft.h',
            'src/kiss/kiss_fftr.c',
            'src/kiss/kiss_fftr.h',
            'src/kiss/kissfft.hh',
            'src/main.cpp',
            'src/ofApp.cpp',
            'src/ofApp.h',
            'src\CircleGrow.cpp',
            'src\CircleGrow.h',
            'src\Layer.cpp',
            'src\Layer.h',
            'src\Overlay.h',
            'src\ParticleGrowTexture.cpp',
            'src\ParticleGrowTexture.h',
            'src\ParticleSystem.cpp',
            'src\ParticleSystem.h',
            'src\ParticleSystemTexture.cpp',
            'src\ParticleSystemTexture.h',
            'src\SimpleDots.cpp',
            'src\SimpleDots.h',
            'src\SimpleStripes.cpp',
            'src\SimpleStripes.h',
            'src\SphereGrow.cpp',
            'src\SphereGrow.h',
            'src\StripeCubes.cpp',
            'src\StripeCubes.h',
            'src\StripeSpiral.cpp',
            'src\StripeSpiral.h',
            'src\TextureGen.h',
            'src\VjObject.cpp',
            'src\VjObject.h',
            'src\WaveMeshAdvTex.cpp',
            'src\WaveMeshAdvTex.h',
            'src\WaveMeshOverlay.cpp',
            'src\WaveMeshOverlay.h',
            'src\WaveMeshTexture.cpp',
            'src\WaveMeshTexture.h',
            'src\main.cpp',
            'src\ofApp.cpp',
            'src\ofApp.h',
        ]

        of.addons: [
            'ofxGui',
            'ofxAnimatable',
            'ofxLayer',
            'ofxOsc',
            'ofxNDI',
            'ofxNetwork',
            'ofxShader',
            'ofxXmlSettings',
        ]

        // This project is using addons.make to include the addons
        // since it was imported from old code. To change it to include
        // the addons from the qbs file change the following lines to
        // the list of used addons in array format. eg:
        //
        // of.addons: [
        //     'ofxGui',
        //     'ofxOpenCv',
        // ]

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

    references: [FileInfo.joinPaths(of_root, "/libs/openFrameworksCompiled/project/qtcreator/openFrameworks.qbs")]
}
