package versioning

import groovy.transform.CompileStatic
import groovy.transform.ToString
import groovy.transform.TypeChecked
import org.joda.time.DateTime

@CompileStatic @TypeChecked
@ToString(includeNames = true)
class RegamedllVersionInfo {
	int majorVersion
	int minorVersion
	Integer maintenanceVersion
	String suffix
	Integer countCommit
	DateTime lastCommitDate

	String format(String versionSeparator, String suffixSeparator, boolean includeSuffix) {
		StringBuilder sb = new StringBuilder()
		sb.append(majorVersion).append(versionSeparator).append(minorVersion)
		if (maintenanceVersion != null) {
			sb.append(versionSeparator).append(maintenanceVersion)
		}

		if (suffix && includeSuffix) {
			sb.append(suffixSeparator).append(suffix)
		}

		return sb.toString()
	}
	String asVersion() {
		sprintf("%i.%i.%i", majorVersion, minorVersion, countCommit)
	}
	String asMavenVersion() {
		format('.', '-', true)
	}
}
