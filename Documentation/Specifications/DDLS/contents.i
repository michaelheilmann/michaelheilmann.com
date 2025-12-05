<h2 id="introduction">1 Introduction</h2>

<p>
This document is the specification of the <em>Data Definition Language Schema</em>, or <em>DDLS</em> for short.
DDLS is a declarative language for defining the structure and constraints for data described by a <a href="@{siteAddress}/specifications/data-definition-language">DDL</a>  programs.
</p>

<p>
<em>DDLS</em> programs and <em>DDL</em> programs are inputs to <em>DDLS validators</em>.
<em>DDLS validators</em> are tools which validate an input DDL program against an input DDLS Schema program.
These tools can be standalone or integrated into libraries and executables.
</p>

<h2 id="ddl-node">2 DDL Node</h2>
<p>A <em>DDL</em> node is a description of data.</p>

<h2 id="ddls-file">3 DDLS File</h2>
<p>A <em>DDLS file</em> is <em>DDL file</em>.
The DDLS file consists of a single definition of a DDLS Schema type.</p>

<h2 id="types">4 Types</h2>
<p>
DDLS types are defined by DDL map values with specific structures and constraints.
</p>

<p>
The following DDLS types exist:

The <em>Any</em> type,
the scalar types
<em>Boolean</em>,
<em>Number</em>,
<em>String</em>, and
<em>Void</em>,
the aggregate types
<em>List</em>, and
<em>Map</em>,
the schema type
<em>Schema</em>,
as well as the schema reference type
<em>Schema Reference</em>.
</p>

<h3 id="any-type">4.1 Any Type</h3>

<h3 id="scalar-type">4.2 Scalar Type</h3>
<p>An <em>Scalar</em> type is represented by a DDL map which consists exactly of the following entries:</p>

<table>
  <tr><td><code>kind</code></td>
  <td>A DDL string representing the kind of the scalar type. The value must be one of "Boolean", "Number", "String", or "Void".
  If the value is "Boolean" then this DDL map represents a <em>Boolean</em> type.
  If the value is "Number" then this DDL map represents <em>Number></em> type.
  If the value is "String" then this DDL map represents <em>String></em> type.
  If the value is "Void" then this DDL map represents <em>Void></em> type.
  </td></tr>
</table>

<h3 id="list-type">4.3 List Type</h3>
<p>A <em>List</em> type is represented by a DDL map which consists exactly of the following entries:</p>

<table>
  <tr><td><code>kind</code></td>
  <td>A DDL string representing the kind of the type. The value must be one of "List".</td></tr>
                                                                                        
  <tr><td><code>entries</code></td>
  <td>The type of the list entries.</td></tr>
</table>

<h3 id="map-type">4.4 Map Type</h3>
<p>
A <em>Map</em> type is represented by a DDL map which consists exactly of the following entries:
</p>

<table>
  <tr><td><code>kind</code></td>
  <td>A DDL string representing the kind of the type. The value must be "Map".</td></tr>
  
  <tr><td><code>entries</code></td>
  <td>
  A DDL map. The names of the map entries are unique.
  The values are types.
  </td>
  </tr>
  
</table>

<h3 id="schema-type">4.5 Schema Type</h3>
<p>
A <em>Schema</em> type is represented by a DDL map which consist exactly of the following entries:

<table>
  <tr><td><code>kind</code></td>
  <td>A DDL string representing the kind of the type. The value must be "Schema".</td></tr>

  <tr><td><code>name</code></td>
  <td>A DDL string representing the name of the schema.</td></tr>  
  
</table>

<h3 id="schema-reference-type">4.6 Schema Reference Type</h3>
<p>
A <em>SchemaReference</em> type is represented by a DDL map which consists exactly of the following entries:
</p>

<table>
  <tr><td><code>kind</code></td>
  <td>A DDL string representing the kind of the type. The value must be "SchemaReference".</td></tr>

  <tr><td><code>name</code></td>
  <td>A DDL string representing the name of the referenced schema.</td></tr>  
  
</table>

<h2 id="validation">Validation</h2>
<p>A <em>validation context</em> consists of one or more schema nodes \(S = \{ s_1,\ldots,s_n \}\) and a starting schema in \(s \in S\).
If \(s \not\in S\) then an <em>schema not found error</em> is raised.
If there exist two schemas \(s_i, s_j \in S\) such that \(i \neq j\) but \(s_i.\textit{name} = s_j.\textit{name}\) then a <em>schema of name already specified</em> error is raised.</p>

<p>
Given a validation context \(S := \{ s_1, \ldots, s_n \}\) and a starting schema \(s \in S\) and a DDL node \(x\), the validation of \(x\) against \((S,s)\) is a recursive process \(\text{validate}\left(S, s, x\right)\).
</p>

<p>\(validate(S, s, x)\):</p>
<ul>
  <li>
  While \(s\) is a DDL schema reference type:
    <ul>
      <li>Find \(s' \in S\) such that \(s'.\text{name} = s.\text{name}\). Raise a <em>SchemaNotFound</em> error if no such \(s'\) was found.</li>
      <li>Let \(s = s'\).</li>
    </ul>
  Invoke \(\text{validate}\left(S, s', x\right)\).
  </li>
  <li>If \(x\) is a DDL boolean value:
      <ul>
        <li>If \(s\) is no DDLS boolean scalar type: a <em>validation error</em> is raised.</li>
      </ul>
  </li>
  <li>If \(x\) is a DDL list value:
      <ul>
        <li>If \(s\) is no DDLS list type: a <em>validation error</em> is raised.</li>
        <li>Otherwise: enter \(\text{listValidation}(S, x, y)\).</li>
      </ul>
  </li>
  <li>If \(x\) is a DDL map value:
      <ul>
        <li>If \(s\) is no DDLS map type: a <em>validation error</em> is raised.</li>
        <li>Otherwise: enter \(\text{mapValidation}(S, x, y)\).</li>
      </ul>
  </li>
  <li>If \(x\) is a DDL number value:
      <ul>
        <li>If \(s\) is no DDLS number scalar type: a <em>validation error</em> is raised.</li>
      </ul>
  </li>
  <li>If \(x\) is a DDL string value:
      <ul>
        <li>If \(s\) is no DDLS string scalar type: a <em>validation error</em> is raised.</li>
      </ul>
  </li>
  <li>If \(x\) is a DDL void value:
      <ul>
        <li>If \(s\) is no DDLS void scalar type: <em>a validation error</em> is raised.</li>
      </ul>
</ul>
