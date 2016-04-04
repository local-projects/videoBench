*this document is a work in progress*

#ClangFormat


###Overview

ClangFormat is a set of tools providing robust automatic code formatting for C, C++, and Objective-C.

It spares you the tedium of manually managed indentation, line breaks, spacing, etc. in your code. ClangFormat makes it easy to spot syntax errors, unmatched brackets, etc. without waiting for the compiler. Most importantly, it makes git diffs more semantic by eliminating noise related to formatting errors and inconsistent code styles.


###Installation

- ClangFormat is available via [Homebrew](http://brew.sh): `brew install clang-format`
- An [Xcode Plugin](https://github.com/travisjeffery/ClangFormat-Xcode) is available a la carte or via the [Alcatraz Package Manager](http://alcatraz.io).
- [Visual Studio Plugin](http://llvm.org/builds/)

The Xcode plugin may be configured to automatically format your code when a file is saved.


###.clang-format Configuration File

The .clang-format file describes a set of formatting rules. We stand to benefit by agreeing upon and sharing a single configuration across developers and projects.

- [.clang-format file specification](http://clang.llvm.org/docs/ClangFormatStyleOptions.html)
- [Interactive guide](http://clangformat.com)

###Exempting Code From Formatting

ClangFormat's output is always correct, but correct isn't always what you want. If you have a format-sensitive section of code you can just can put flags in comments around the code you'd like ClangFormat to ignore:

	stuff that will be formatted
	
	// clang-format off
	
	stuff that won’t be formatted
	
	// clang-format on
	
	stuff that will be formatted
 
 
###Questions
- How to deal with non-compliant third-party projects like openFrameworks?-
- How and where to store .clang-format files and deal with inevitable variations across projects. In the repository root? Do we need to modify the IDE plugins to ascend the file tree and use the first file it finds? (For example, a project with the if a project has multiple submodules with 
- How can we agree on a shared .clang-format configuration? Tabs vs. spaces, etc.
