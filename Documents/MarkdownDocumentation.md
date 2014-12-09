Getting started with Markdown
===
This page offers a brief overview of what it's like to use Markdown.
Markdown should be very easy to pick up simply by looking at a few examples of it in action.
The examples on this page are written in a before/after style, showing example syntax and the HTML output produced by Markdown.

**NOTE**: this page is written in **Markdown** using **MarkEdit**  `:-)`
Contents
---

+ Paragraphs, Headers, Blockquotes
+ Phrase Emphasis
+ Lists
+ Links
+ Images

-----------------------------------------------------------------
Paragraphs, Headers, Blockquotes
===

A paragraph is simply one or more consecutive lines of text, separated by one or more blank lines.
(A blank line is any line that looks like a blank line - a line containing nothing but spaces or tabs is considered blank.)
Normal paragraphs should not be indented with spaces or tabs.


Markdown offers two styles of headers: 

+ Setext
+ Aex

###Setext

Setext-style headers for `<h1\>` and `<h2\>` are created by “underlining” with equal signs (`=`) and hyphens (`-`)

__Markdown:__

	A First Level Header
	====================
	A Second Level Header
	--------------------

__HTML output:__

	<h1>A First Level Header</h1>
	<h2>A Second Level Header</h2>

###Atex

Atx-style header are created by puting 1-6 hash marks (`#`) at the beginning of the line where the number of hashes equals the resulting HTML header level.

__Markdown:__

	#This is First Level Header
	##This is Second Level Header
	###This is Third Level Header

__HTML output:__

	<h1>This is First Level Header</h1>
	<h2>This is Second Level Header</h2>
	<h3>This is Third Level Header</h3>
-----------------------------------------------------------------

Phrase Emphasis
===
Markdown uses asterisks and underscores to indicate spans of emphasis.

__Markdown:__

	Some of these words *are emphasized*.
	Some of these words _are emphasized also_.

	Use two asterisks for **strong emphasis**.
	Or, if you prefer, __use two underscores instead__.

__HTML output:__

	<p>Some of these words <em>are emphasized</em>.
	Some of these words <em>are emphasized also</em>.</p>

	<p>Use two asterisks for <strong>strong emphasis</strong>.
	Or, if you prefer, <strong>use two underscores instead</strong>.</p>
-----------------------------------------------------------------
Lists
---

###Unordered lists
Unordered (bulleted) lists use asterisks, pluses, and hyphens (`*`, `+`, and `-`) as list markers. These three markers are interchangable; this:

	*   Candy.
	*   Gum.
	*   Booze.
and this:

	+   Candy.
	+   Gum.
	+   Booze.

also this:
	
	-   Candy.
	-   Gum.
	-   Booze.

all produce the same output:

	<ul>
		<li>Candy.</li>
		<li>Gum.</li>
		<li>Booze.</li>
	</ul>

###Ordered lists
Ordered (numbered) lists use regular numbers, followed by periods, as list markers:

__Markdown:__

	1.  Red
	2.  Green
	3.  Blue

__HTML output:__

	<ol>
		<li>Red</li>
		<li>Green</li>
		<li>Blue</li>
	</ol>

If you put blank lines between items, you’ll get `<p>` tags for the list item text. You can create multi-paragraph list items by indenting the paragraphs by 4 spaces or 1 tab:

__Markdown:__

	*   A list item.

		With multiple paragraphs.

	*   Another item in the list.

__HTML output:__

	<ul>
		<li><p>A list item.</p>
		<p>With multiple paragraphs.</p></li>
		<li><p>Another item in the list.</p></li>
	</ul>
-----------------------------------------------------------------
Links
---

Markdown supports two styles for creating links: _inline_ and _reference_. With both styles, you use square brackets to delimit the text you want to turn into a link.

###Inline-style links
Inline-style links use parentheses immediately after the link text.
__Markdown:__

	This is an [example link](http://example.com/).

__HTML output:__

	<p>This is an <a href="http://example.com/">example link</a>.</p>

Optionally, you may include a title attribute in the parentheses:

__Markdown:__

	This is an [example link](http://example.com/ "With a Title").

__HTML output:__
	
	<p>This is an <a href="http://example.com/" title="With a Title">example link</a>.</p>

###Reference-style links
Reference-style links allow you to refer to your links by names, which you define elsewhere in your document:

__Markdown:__

	I get 10 times more traffic from [Google][1] than from [Yahoo][2] or [MSN][3].

	[1]: http://google.com/        "Google"
	[2]: http://search.yahoo.com/  "Yahoo Search"
	[3]: http://search.msn.com/    "MSN Search"

__HTML output:__

	<p>I get 10 times more traffic from <a href="http://google.com/" title="Google">Google</a> than from <a href="http://search.yahoo.com/" title="Yahoo Search">Yahoo</a> or <a href="http://search.msn.com/" title="MSN Search">MSN</a>.</p>

The title attribute is optional. Link names may contain letters, numbers and spaces, but are not case sensitive:

__Markdown:__

	I start my morning with a cup of coffee and
	[The New York Times][NY Times].

	[ny times]: http://www.nytimes.com/

__HTML output:__

	<p>I start my morning with a cup of coffee and <a href="http://www.nytimes.com/">The New York Times</a>.</p>

-----------------------------------------------------------------
Images
---
Image syntax is very much like link syntax. and supports both previous styles too.
###Inline-style images
__NOTE:__ titles are optional

__Markdown:__

	![alt text](/path/to/img.jpg "Title")


###Reference-style images

__Markdown:__

	![alt text][id]

	[id]: /path/to/img.jpg "Title"

both styles will produce the same HTML output:

__HTML output:__

	<img src="/path/to/img.jpg" alt="alt text" title="Title" />

-----------------------------------------------------------------
Code
---

In a regular paragraph, you can create code span by wrapping text in backtick quotes. Any ampersands (&) and angle brackets (< or >) will automatically be translated into HTML entities. This makes it easy to use Markdown to write about HTML example code:

__Markdown:__

	I strongly recommend against using any `<blink>` tags.

	I wish SmartyPants used named entities like `&mdash;`
	instead of decimal-encoded entites like `&#8212;`.

__HTML output:__

	<p>I strongly recommend against using any
	<code>&lt;blink&gt;</code> tags.</p>

	<p>I wish SmartyPants used named entities like
	<code>&amp;mdash;</code> instead of decimal-encoded entites like <code>&amp;#8212;</code>.</p>

To specify an entire block of pre-formatted code, indent every line of the block by 4 spaces or 1 tab. Just like with code spans, &, <, and > characters will be escaped automatically.

If you want your page to validate under XHTML 1.0 Strict,
you've got to put paragraph tags in your blockquotes.

__Markdown:__

    <blockquote>
        <p>For example.</p>
    </blockquote>

__HTML output:__

	<p>If you want your page to validate under XHTML 1.0 Strict,
	you've got to put paragraph tags in your blockquotes:</p>

	<pre><code>&lt;blockquote&gt;
	&lt;p&gt;For example.&lt;/p&gt;
	&lt;/blockquote&gt;
</code></pre>
