project(IRECore)

add_library(IRECore
    # Hearders
    
    IRECore.h

    # Sources

    IRECore.cpp
)



set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 17)
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD_REQUIRED ON)

target_link_libraries(IRECore sfml-graphics sfml-audio sfml-window sfml-system)
