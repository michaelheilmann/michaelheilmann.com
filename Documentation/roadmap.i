  @{include("./Commons/header-common.i")}
  <link rel='stylesheet' href='https://michaelheilmann.com/assets/reset.css'>
  <link rel='stylesheet' href='https://michaelheilmann.com/assets/index.css'>
  <link rel='canonical' href='https://michaelheilmann.com/roadmap.html' />
  <title>Roadmap</title>
</head>
<body class="my-content-page-1">
  <header></header>
  <main>
    <h1>Roadmap</h1>
    
    <h2>Milestone 6: Separate website sources and product</h2>
    <p>Percentage done: 0&percnt;, Due date: Week 1 October 2024</p>
    <p>The website shall be generated in a dedicated `.build` folder of the repository.
    This will result in reduces sizes of the uploads to webhosts.</p>
    
    <h2>Milestone 5: Maintain roadmap on website</h2>
    <p>Percentage done: 100&percnt;, Due date: Week 1 October 2024</p>
    <p>The roadmap shall be maintained on the website.</p>
    
    <h2>Milestone 4: Tooling for generating icons and banners (Windows only) | Tools.BannerGenerator</h2>
    <p>Percentage done: 100&percnt;, Due date: Week 4 September 2024</p>
    
    <p>
    Certain operating systems (in particular Windows) require banners for application installers.
    We require a tool to generate those.</p>
    <p>
    The banner generator generates a "PNG" file.
    As parameters, it takes the width and the height of the banner and the path of the "PNG" file.
    The generated "PNG" file is an opaque black banner.
    </p>
    
    <h2>Milestone 3: Tooling for generating icons (Windows only) | Tools.IconGenerator</h2>
    <p>Percentage done: 100&percnt;, Due date: Week 3 September 2024</p>
    
    <p>
    Certain operating systems (in particular Windows) require Icons for application windows and application installers.
    We require a tool to generate those.
    </p>
    
    <p>
    The icon generator generates an "ICO" file.
    As parameter, it takes the path of the "ICO" file.
    The generated "ICO" file contains opaque black black icons of the sizes 8x8, 16x16, 24x24, 32x32, 48x48, 64x64, 96x96, 128x128, and 256x256.
    </p>
    
    <h2>Milestone 2: Tooling for building the website | Tools.TemplateEngine</h2>
    <p>Percentage done: 100&percnt;, Due date: Week 2 September 2024</p>
    
    <p>
    The source code of the website consists of multiple <code>.t</code> files.
    The tool <i>Tools.TemplateEngine</i> reads <code>.t</code> files and creates the output <code>.html</code> files.
    </p>
    
    <p>
    The tool works as follows: It receives the filename of one <code>.t</code> file and the filename of the target <code>.html</code> file.
    It will <i>parse</i> the <code>.t</code> file to create the target <code>.html</code> file.
    <i>parsing</i> means that the contents of the <code>.t</code> file are written to the target file unlesss directives are encountered.
    The directives are not written to the target file. Instead, they are interpreted. There are two kinds of directives:
    </p>
    <ul>
      <li><code>@@@@</code> directive results in <code>@@</code> in being written to the target file.</li>
      <li><code>@@include(&lt;filename&gt;)</code> directive *parses* the file specified by <code>&lt;filename&gt;</code>.
    </ul>
    <p>
    Recursive include directives yield an error.
    The parser must support UTF-8-NO-BOM encoding.
    </p>
    
    <h2>Milestone 1: Improve tooling to build the website | Tools.Concatenate</h2>
    <p>Percentage done: 100&percnt;, Due date: Week 1 September 2024</p>
    
    <p>
    The source code of the website consists of multiple <code>.t</code> files.
    The tool <i>Tools.Concatenate</i> reads the  <code>.t</code> files and creates the output <code>.html</code> files.
    </p>
    
    <p>
    The tool works as follows: It receives the filename of a one or more <code>.t</code> files and the filename of the target <code>.html</code> file.
    It will then concatenate the Bytes of the <code>.t</code> files (in the order they were specified) and write the Bytes to the <code>.html</code> file.
    </p>
  </main>
  <footer>
    <span style="font-style: italic">Webite maintained by Michael Heilmann. Last modified on 6 October 2024.</span>
  </footer>
</body>
</html>