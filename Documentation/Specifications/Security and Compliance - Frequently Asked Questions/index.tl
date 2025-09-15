  @{include("./../../Documentation/Commons/header-common.i")}
  <link rel='stylesheet' href='@{siteAddress}/assets/reset.css?v=4'>
  <link rel='stylesheet' href='@{siteAddress}/assets/index.css?v=4'>
  <link rel='canonical' href='@{siteAddress}/specifications/compliance-guide/index.html'>
  <title>Compliance Guide</title>
  <style>
  @{include("./Specifications/specification.css.i")} 
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
    <h1>Security and Compliance Frequently Asked Questions</h1>
    <summary style="font-style: italic">
    @{include("./Specifications/Security and Compliance - Frequently Asked Questions/0.summary.i")}
    </summary>
    
    <h2 id="introduction">1 Introduction</h2>
    @{include("./Specifications/Security and Compliance - Frequently Asked Questions/0.summary.i")}
    
    @{include("./Specifications/Security and Compliance - Frequently Asked Questions/1.general-data-protection-regulation.i")}
    @{include("./Specifications/Security and Compliance - Frequently Asked Questions/2.artificial-intelligence-act.i")}
                

    
  </div>
  <div class="right-column">
    <nav>
      <ul style="list-style: none">
        <li><a href="#introduction">1. Introduction</a></li>
        <li><a href="#general-data-protection-regulation">2. General Data Protection Regulation</a></li>
        <li><a href="#articial-intelligence-act">3. Artificial Intelligence Act</a></li>
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
