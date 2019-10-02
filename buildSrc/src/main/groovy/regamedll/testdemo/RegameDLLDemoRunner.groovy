package regamedll.testdemo

import dirsync.builder.FileSystemTreeBuilder
import dirsync.merger.FileTreeComparator
import dirsync.merger.FileTreeDiffApplier
import dirsync.model.tree.DirectoryNode
import dirsync.model.tree.FSMapper
import dirsync.model.tree.ZipData
import dirsync.model.tree.ZipTreeMapper
import org.apache.ant.compress.taskdefs.Unzip
import org.apache.tools.ant.types.PatternSet;

class RegamedllDemoRunner {
    ZipTreeMapper regamedllImage = new ZipTreeMapper()
    File rootDir
    DirectoryNode<ZipData> engineImageTree
    Closure postExtract

    static class TestResult {
        boolean success
        int returnCode
        String hldsConsoleOutput
        long duration
    }

    RegamedllDemoRunner(Collection<File> engineImageZips, File rootDir, Closure postExtract) {
        this.rootDir = rootDir
        engineImageZips.each { f ->
            regamedllImage.addZipArchive(f.absolutePath)
        }
        engineImageTree = regamedllImage.buildFileTree()
        this.postExtract = postExtract
    }

    void prepareDemo(File demoArchive) {

	if (demoArchive == null) {
		throw new RuntimeException("ReGameDLL_CS testdemos: file is null")
	}

	PatternSet patt = new PatternSet();

	patt.setExcludes("**/*.bin");
	patt.setExcludes("**/*.xml");

	//patt.setIncludes("**/cstrike/*");
	//patt.setIncludes("**/czero/*");
	//patt.setIncludes("**/valve/*");

        Unzip unzipper = new Unzip();

	unzipper.setDest( rootDir ); // directory unzipped
	unzipper.setSrc( demoArchive ); // zip file
	unzipper.addPatternset( patt );
	unzipper.execute();
    }

    void prepareEngine() {
        def existingTree = FileSystemTreeBuilder.buildFileSystemTree(rootDir)
        def cmds = FileTreeComparator.mergeTrees(engineImageTree, existingTree)

        FSMapper fsMapper = new FSMapper(rootDir)
        FileTreeDiffApplier.applyDiffs(cmds, regamedllImage, fsMapper)
        if (postExtract != null) {
            postExtract.run()
        }
    }

    TestResult runTest(RegamedllTestInfo info, File testLogDir) {
        long startTime = System.currentTimeMillis()

        //prepareEngine()

        def outPath = new File(testLogDir, "${info.testName}_run.log")

        def cmdParams = []
        cmdParams << new File(rootDir, 'hlds.exe').absolutePath
        cmdParams.addAll(info.hldsArgs)
        if (info.regamedllExtraArgs) {
            cmdParams.addAll(info.regamedllExtraArgs)
        }
        cmdParams << '--rehlds-test-play' << info.testBinFile.absolutePath

        def pb = new ProcessBuilder(cmdParams).redirectErrorStream(true).directory(rootDir)
        def sout = new StringBuffer()

        def p = pb.start()
        p.consumeProcessOutput(sout, sout)

        p.waitForOrKill(info.timeoutSeconds * 1000)
        int exitVal = p.exitValue()

        outPath.withWriter('UTF-8') { writer ->
            writer.write(sout.toString())
        }

        long endTime = System.currentTimeMillis()

        return new TestResult(
                success: (exitVal == 777),
                returnCode: exitVal,
                hldsConsoleOutput: sout.toString(),
                duration: endTime - startTime
        )
    }
}
