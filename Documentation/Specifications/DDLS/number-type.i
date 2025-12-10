<h3 id="number-type">3.5 Number types</h3>
<p>The values of type \(\textit{Number}_{\textit{DDLS}}\) are represented by a \(\textit{Map}\) values.
   The map contains a single map entry of name \(\texttt{kind}\) with the value \(\texttt{Number}\) of type
   \(\textit{String}\).</p>

<p>The translation function is hence given by</p>
<table class="syntax-directed-translation">
  <tr>
    <td>
    <my-formula-box class="align-left">\[\begin{array}{ll}
      \left[\left( \texttt{kind}, \texttt{Number} \right) \right]@@1
    \end{array}\]</my-formula-box>
    </td>
    <td>
    <my-formula-box class="align-right">\[\begin{array}{ll}
      1.\text{value} = \textit{number}_{\textit{DDLS}}
    \end{array}\]</my-formula-box>
    </td>
  </tr>
</table>
<p>where \(\textit{number}_{\textit{DDLS}}\) is the single value of type \(\textit{Number}_{\textit{DDLS}}\).</p>
