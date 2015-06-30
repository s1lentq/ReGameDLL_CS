package gradlecpp

import org.gradle.api.Plugin
import org.gradle.api.Project

class RegamedllPlayTestPlugin implements Plugin<Project> {
    @Override
    void apply(Project project) {
        project.configurations {
            regamedll_playtest_image
        }

        project.dependencies {
            regamedll_playtest_image 'regamedll.testimg:testimg:1.0'
        }
    }
}
