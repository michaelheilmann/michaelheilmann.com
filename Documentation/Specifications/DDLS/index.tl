  @{include("./../../Commons/header-common.i")}
  <link rel='stylesheet' href='@{siteAddress}/assets/reset.css?v=3'>
  <link rel='stylesheet' href='@{siteAddress}/assets/index.css?v=3'>
  <link rel='canonical' href='@{siteAddress}/specifications/data-definition-language/index.html'>
  <script id="MathJax-script" async src="https://cdn.jsdelivr.net/npm/mathjax@@4/tex-mml-chtml.js"></script>
  <title>Data Definition Language Schema (draft, v0.1)</title>
  <style>
  @{include("./../specification.css.i")}
  my-sem, my-syn, my-lex {
    font-family: my-code-font, monospace;
  }
  my-syn::after {
    content: "<sub>syn/sub>"
  }
  my-sem {
    font-style: italic;
    font-family: my-default-font;
  }
  my-sem::after {
    content: "<sub>sem</sub>"
  }
  </style>
</head>
<body class="my-content-page-1">
  <header>
  <div>
  <a href="@{siteAddress}/">Home</a>
  </div>
  </header>
  <main>
    <div class="left-column"></div>
    <div class="center-column">
    <h1>Data Definition Language Schema (draft, v0.1)</h1>
    @{include("./contents.i")}
  </div>
  <div class="right-column">
   <nav>
      <ul style="list-style: none">
        <li><a href="#introduction">1 Introduction</a></li>
        <li><a href="#ddl-node">2 DDL Node</a></li>
        <li><a href="#ddl-schema-node">3 DDL Schema Node</a></li>
        <li><a href="#validation-context">4 Validation Context</a></li>
        <li><a href="#types">5 Types</a></li>
      </ul>
    </nav>
  </div>
  </main>
  <footer>
    <div class="left-column"></div>
    <div class="center-column"></div>
    <div class="right-column">
      <div>Website maintained by @{siteAuthor}.</div>
      <div>Last modified on @{dayOfMonth()} @{monthName()} @{year()}.</div>
    </div>
  </footer>
</body>
</html>
