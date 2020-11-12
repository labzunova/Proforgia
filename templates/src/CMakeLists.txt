set(template_source
        View.cpp
        QueueOfPart.cpp
        Part.cpp
        Parser.cpp
        Loader.cpp
        Context.cpp)

add_library(templates STATIC ${template_source})