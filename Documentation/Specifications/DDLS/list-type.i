<h3 id="list-type">3.3 List type</h3>
<p>Values of type \(\textit{List}_{\textit{DDLS}}\) are represented by a \(\textit{Map}\) values.
   The map contains two entries.</p>

<ul>
  <li>\(\left(\texttt{kind}, \texttt{List}\right)\) where \(\texttt{List}\) is of type \(\textit{String}\).</li>
  <li>\(\left(\texttt{elements}, x\right)\) where \(x\) is a value of type \(\textit{Value}_{\textit{DDLS}}\) value.</li>
</ul>

<p>The translation function is hence given by</p>
<table class="syntax-directed-translation">
  <tr>
    <td>
    <my-formula-box class="align-left">\[\begin{array}{ll}
      \left[ \left(\texttt{kind},\texttt{List}\right), \left(\texttt{elements}, w@@2 \right) \right]@@1
    \end{array}\]</my-formula-box>
    </td>
    <td>
    <my-formula-box class="align-right">\[\begin{array}{ll}
      1.\text{value} = 1.\text{value}
    \end{array}\]</my-formula-box>
    </td>
  </tr>
</table>
