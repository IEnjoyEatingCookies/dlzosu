#include <visualizer/osu.h>

using final_project::visualizer::Osu;

void prepareSettings(Osu::Settings* settings) {
}

// This line is a macro that expands into an "int main()" function.
CINDER_APP(Osu, ci::app::RendererGl(ci::app::RendererGl::Options().msaa(2)), prepareSettings);
