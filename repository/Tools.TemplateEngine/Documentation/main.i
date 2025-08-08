<main>
<div class="left-column"></div>
<div class="center-column">
  <h1>Michael Heilmann's Arcadia Template Engine</h1>
  <p>
  This is the documentation for Michael Heilmann's Arcadia Template Engine.
  The Template Engine is a template engine primarily used to generate websites.
  </p>
  
  <p>
  The Template Engine can be invoked by the following command (assuming the executable <code>Arcadia.TemplateEngine</code> is in your path).
  </p>
  <p><code>
  Arcadia.TemplateEngine <my-mv>source file</my-mv> <my-mv>target file</my-mv> <my-mv>environment file</my-mv>
  </code></p>
  
  <p><my-mv>source file</my-mv> is the path to the source file (relative to the working directory).<p>
  <p><my-mv>target file</my-mv> is the path to the target file (relative to the working directory).<p>
  
  The parsing of the input file allows for transforming and augmenting
  The Template Engine provides built-in expressions to include the contents of a file, to emit date/time information.
  </p>

  @{include("1.files.i")}
  @{include("2.how_arms_works.i")}
  @{include("3.starting_up_and_shutting_down.i")}
  @{include("4.managed-memory.i")}
  @{include("5.unmanaged-memory.i")}
</div>
<div class="right-column"></div>
</main>
