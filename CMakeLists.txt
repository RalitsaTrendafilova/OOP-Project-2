cmake_minimum_required(VERSION 3.20)
project(OOP_Project_2)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(OOP_Project_2
        AddImageToSession.cpp
        AddImageToSession.h
        AddTransformationToImageInSessionCommand.cpp
        AddTransformationToImageInSessionCommand.h
        ApplicationController.cpp
        ApplicationController.h
        ApplyGrayscale.cpp
        ApplyGrayscale.h
        ApplyMonochrome.cpp
        ApplyMonochrome.h
        ApplyNegative.cpp
        ApplyNegative.h
        ApplyRotation.cpp
        ApplyRotation.h
        MakeCollageCommand.cpp
        MakeCollageCommand.h
        RasterImage.cpp
        RasterImage.h
        RasterImageBase.cpp
        RasterImageBase.h
        RasterImageCL.cpp
        RasterImageRW.cpp
        RasterImageRW.h
        Session.cpp
        Session.h
        SessionCommandBase.h
        TransformationBase.h)
