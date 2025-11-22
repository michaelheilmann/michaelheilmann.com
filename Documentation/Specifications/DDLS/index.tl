  @{include("./../../Commons/header-common.i")}
  <link rel='stylesheet' href='@{siteAddress}/assets/reset.css?v=3'>
  <link rel='stylesheet' href='@{siteAddress}/assets/index.css?v=3'>
  <link rel='canonical' href='@{siteAddress}/specifications/data-definition-language/index.html'>
  <title>Data Definition Language</title>
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
    <h1>Data Definition Language Schema</h1>

    @{include("./1.introduction.i")}

  </div>
  <div class="right-column">
   <nav>
      <ul style="list-style: none">
        <li><a href="#introduction">1 Introduction</a></li>
        %<li><a href="#lexical-specification">2 Lexical Specification</a></li>
        %<li><a href="#syntactical-specification">3 Syntactical Specification</a></li>
        <li><a href="#semantical-specification">4 Semantical Specification</a></li>
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
