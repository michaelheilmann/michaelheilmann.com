<h3 id="map-type">3.4 Map type</h3>
<p>A value of type \(\textit{Map}_{\textit{DDLS}}\) are represented by a \(\textit{Map}\) value.
   The map contains two entries.</p>

<ul>
  <li>\(\left(\texttt{kind}, \texttt{Map}\right)\) where \(\texttt{Map}\) is of type \(\textit{String}\).</li>
  <li>\(\left(\texttt{entries}, w\right)\) where \(w\) is \(\textit{List}\) value with elements of type \(\textit{MapEntry}_{\textit{DDLS}}\).</li>
</ul>

<p>The translation function is hence given by</p>
<table class="syntax-directed-translation">
  <tr>
    <td>
    <my-formula-box class="align-left">\[\begin{array}{ll}
      \left[ \left(\texttt{kind},\texttt{Map}\right), \left(\texttt{entries}, w@@2 \right) \right]@@1
    \end{array}\]</my-formula-box>
    </td>
    <td>
    <my-formula-box class="align-right">\[\begin{array}{ll}
      1.\text{value} =
      \begin{cases}
        \left[ 2.\text{value} \right]  & \text{if } 2.\text{value} \not\in \textit{Error}_{\textit{DDLS}}\text{,}\\
      \textit{Error}_{\textit{DDLS}} & \text{otherwise.}
      \end{cases}
    \end{array}\]</my-formula-box>
    </td>
  </tr>
  <tr>
    <td>
    <my-formula-box class="align-left">\[\begin{array}{ll}
      \left(w@@1\right) \text{if }w = [x] \circ{v}
    \end{array}\]</my-formula-box>
    </td>
    <td>
    <my-formula-box class="align-right">\[\begin{array}{ll}
      1.\text{value} =
      \begin{cases}
        \left[x.\text{value}\right] \circ v.\text{value}
          &\text{if } x.\textit{value} \in\textit{MapEntry}_{\textit{DDLS}}, v.\text{value} \not\in \textit{Error}_{\textit{DDLS}}\\
        \textit{Error}_{\textit{DDLS}}
          &\text{otherwise.}
      \end{cases}
    \end{array}\]</my-formula-box>
    </td>
  </tr>
  <tr>
    <td>
    <my-formula-box class="align-left">\[\begin{array}{ll}
      \left(w@@1\right) \text{if }w = []
    \end{array}\]</my-formula-box>
    </td>
    <td>
    <my-formula-box class="align-right">\[\begin{array}{ll}
      1.\textit{value} = []
    \end{array}\]</my-formula-box>
    </td>
  </tr>
</table>

<p>A value of type \(\textit{MapEntry}_{\textit{DDLS}}\) are represented by a \(\textit{Map}\) value.
   The map contains three entries.</p>

<ul>
  <li>\(\left(\texttt{kind}, \texttt{MapEntry}\right)\) where \(\texttt{MapEntry}\) is of type \(\textit{String}\).</li>
  <li>\(\left(\texttt{name}, a\right)\) where \(a\) is a value of type \(\textit{String}\).</li>
  <li>\(\left(\texttt{type}, b\right)\) where \(b\) is a value of type \(\textit{Value}_{\textit{DDLS}}\).</li>
</ul>

<p>The translation function for a \(\textit{MapEntry}_{\textit{DDLS}}\) is hence given by</p>
<table class="syntax-directed-translation">
  <tr>
    <td>
    <my-formula-box class="align-left">\[\begin{array}{ll}
     \left[\left(\texttt{kind},\texttt{MapEntry}\right),
          \left(\texttt{name}, a\right),
          \left(\texttt{type}, b\right)
     \right]@@1
    \end{array}\]</my-formula-box>
    </td>
    <td>
    <my-formula-box class="align-right">\[\begin{array}{ll}
    1.\text{value} =
      \begin{cases}
      \left(a, b.\text{value}\right) &\text{if }b.\text{value}\not\in\textit{Error}_{\textit{DDLS}}\text{,}\\
      \textit{Error}_{\textit{DDLS}} &\text{otherwise.}
      \end{cases}
    \end{array}\]</my-formula-box>
    </td>
  </tr>
</table>
