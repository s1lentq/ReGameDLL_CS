package gradlecpp

import gradlecpp.teamcity.TeamCityIntegration
import org.apache.commons.lang.SystemUtils
import org.gradle.api.DefaultTask
import org.gradle.api.file.FileCollection
import org.gradle.api.tasks.TaskAction
import org.gradle.nativeplatform.NativeBinarySpec
import regamedll.testdemo.RegamedllDemoRunner
import regamedll.testdemo.RegamedllTestParser

class RegamedllPlayTestTask extends DefaultTask {

    def FileCollection testDemos
    def Closure postExtractAction
    def File regamedllImageRoot
    def File regamedllTestLogs
    def NativeBinarySpec testFor

    @TaskAction
    def doPlay() {
        if (!SystemUtils.IS_OS_WINDOWS) {
            return
        }

        if (!testDemos) {
            println 'RegamedllPlayTestTask: no demos attached to the testDemos property'
        }

        regamedllImageRoot.mkdirs()
        regamedllTestLogs.mkdirs()

        def demoRunner = new RegamedllDemoRunner(this.project.configurations.regamedll_playtest_image.getFiles(), regamedllImageRoot, postExtractAction)

        println "Preparing engine..."
        demoRunner.prepareEngine()

        println "Running ${testDemos.getFiles().size()} ReGameDLL_CS test demos..."

        TeamCityIntegration.suiteStarted("regamedllDemo.${testFor.name}")
        int failCount = 0;
	testDemos.getFiles().each { f ->

            demoRunner.prepareEngine();
            def testInfo = RegamedllTestParser.parseTestInfo(f)

            TeamCityIntegration.testStarted(testInfo.testName)

            if (!TeamCityIntegration.writeOutput) {
                println "Running ReGameDLL_CS test demo ${testInfo.testName} "
                System.out.flush()
            }

            println "Preparing files for test demo ${testInfo.testName} "

            demoRunner.prepareDemo(f)

            def testRes = demoRunner.runTest(testInfo, regamedllTestLogs)

            if (testRes.success) {
                if (!TeamCityIntegration.writeOutput) {
                    println ' OK'
                }
            } else {

                TeamCityIntegration.testFailed(testInfo.testName, "Exit code: ${testRes.returnCode}", "Exit code: ${testRes.returnCode}")
                if (!TeamCityIntegration.writeOutput) {
                    println ' Failed'
                    println "ReGameDLL_CS testdemo ${testInfo.testName} playback failed. Exit status is ${testRes.returnCode}."
                    println "Dumping console output:"
                    println testRes.hldsConsoleOutput
                }

                failCount++
            }

            TeamCityIntegration.testStdOut(testInfo.testName, testRes.hldsConsoleOutput)
            TeamCityIntegration.testFinished(testInfo.testName, testRes.duration)
        }
        TeamCityIntegration.suiteFinished("regamedllDemo.${testFor.name}")

        if (failCount) {
            throw new RuntimeException("ReGameDLL_CS testdemos: failed ${failCount} tests")
        }
    }
}
