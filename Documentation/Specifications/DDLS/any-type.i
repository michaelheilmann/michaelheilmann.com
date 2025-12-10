<h3 id="any-type">3.1 Any type</h3>
<p>The values of type \(\textit{Any}_{\textit{DDLS}}\) are represented by \(\textit{Map}\) values.
   The map contains a single map entry of name \(\texttt{kind}\) with the value \(\texttt{Any}\) of type 
   \(\textit{String}\).</p>

<p>The translation function is hence given by</p>
<table class="syntax-directed-translation">
  <tr>
    <td>
    <my-formula-box class="align-left">\[\begin{array}{ll}
      \left[ \left( \texttt{kind},\texttt{Any} \right) \right]@@1
    \end{array}\]</my-formula-box>
    </td>
    <td>
    <my-formula-box class="align-right">\[\begin{array}{ll}
      1.\text{value} = \textit{any}_{\textit{DDLS}}
    \end{array}\]</my-formula-box>
    </td>
  </tr>
</table>
<p>where \(\textit{any}_{\textit{DDLS}}\) is the single value of type \(\textit{Any}_{\textit{DDLS}}\).</p>
