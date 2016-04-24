package versioning

import groovy.transform.CompileStatic
import groovy.transform.TypeChecked
import org.eclipse.jgit.api.Git
import org.eclipse.jgit.lib.ObjectId
import org.eclipse.jgit.lib.Repository
import org.eclipse.jgit.lib.StoredConfig
import org.eclipse.jgit.revwalk.RevCommit
import org.eclipse.jgit.revwalk.RevWalk
import org.eclipse.jgit.storage.file.FileRepositoryBuilder
import org.joda.time.DateTime
import org.joda.time.DateTimeZone

@CompileStatic @TypeChecked
class GitVersioner {

	static GitInfo versionForDir(String dir) {
		versionForDir(new File(dir))
	}
	static int getCountCommit(Repository repo) {
		Iterable<RevCommit> commits = Git.wrap(repo).log().call()
		int count = 0;
		commits.each {
			count++;
		}

		return count;
	}
	// return last commit excluding merge commit 
	static RevCommit parseCommitLast(Repository repo) {
		Iterable<RevCommit> commits = Git.wrap(repo).log().call()
		for (RevCommit b : commits) {
			if (b.getParents().length > 1) { // it's merge commit ignore it
				continue;
			}
			return b;
		}

		return null;
	}
	static String prepareUrlToCommits(String url) {
		if (url == null) {
			// default remote url
			return "https://github.com/s1lentq/ReGameDLL_CS/commit/";
		}

		StringBuilder sb = new StringBuilder();
		String childPath;
		int pos = url.indexOf('@');
		if (pos != -1) {
			childPath = url.substring(pos + 1, url.lastIndexOf('.git')).replace(':', '/');
			sb.append('https://');
		} else {
			childPath = url.substring(0, url.lastIndexOf('.git'));
		}

		sb.append(childPath).append('/commit/');
		return sb.toString();
	}
	static GitInfo versionForDir(File dir) {
		FileRepositoryBuilder builder = new FileRepositoryBuilder()
		Repository repo = builder.setWorkTree(dir)
			.findGitDir()
			.build()

		ObjectId head = repo.resolve('HEAD')
		if (!head) {
			return null
		}

		final StoredConfig cfg = repo.getConfig();
		def commit = new RevWalk(repo).parseCommit(head)
		def commitLast = parseCommitLast(repo)
		int commitCount = getCountCommit(repo)

		def branch = repo.getBranch()
		def commitDate = new DateTime(1000L * commit.commitTime, DateTimeZone.UTC)

		String url = null;
		String remote_name = cfg.getString("branch", branch, "remote");

		if (remote_name == null) {
			for (String remotes : cfg.getSubsections("remote")) {
				if (url != null) {
					println 'Found a second remote: (' + remotes + '), url: (' + cfg.getString("remote", remotes, "url") + ')'
					continue;
				}

				url = cfg.getString("remote", remotes, "url");
			}
		} else {
			url = cfg.getString("remote", remote_name, "url");
		}

		println 'Debug: Start';
		println '	cfg: (' + cfg + ')';
		println '	branch: (' + branch + ')';
		println '	remote_name: (' + remote_name + ')';
		println '	url: (' + url + ')';
		println 'Debug: End';

		String urlCommits = prepareUrlToCommits(url);

		if (!commit) {
			throw new RuntimeException("Can't find last commit.")
		}

		String tag = repo.tags.find { kv -> kv.value.objectId == commit.id }?.key
		String headCommitId = commit.getId().abbreviate(7).name();
		String authorCommit = commitLast.getAuthorIdent().getName();

		return new GitInfo(
			lastCommitDate: commitDate,
			branch: branch,
			tag: tag,
			countCommit: commitCount,
			commitID: headCommitId,
			authorCommit: authorCommit,
			urlCommits: urlCommits
		)
	}
}
