<h4 id="Arcadia_safeMultiply*">Arcadia_safeMultiply*</h4>
<p>Get the product of two values.</p>
<p><code>
void
Arcadia_safeMultiply<my-mv>Suffix</my-mv>
  (
    Arcadia_Thread* thread,
    <my-mv>Type<my-mv> x,
    <my-mv>Type<my-mv> y
  )
</code></p>
<p>The following table lists the combinations of <my-mv>Type</my-mv> and <my-mv>Suffix</my-mv> for which the above functions are defined</p>

<table>
<tr><td><my-mv>Suffix</my-mv></td> <td><my-mv>Type</my-mv></td></tr>
<tr><td><code>Natural8Value</code></td><td><code>Arcadia_Natural8Value</code></td></tr>
<tr><td><code>Natural16Value</code></td><td><code>Arcadia_Natural16Value</code></td></tr>
<tr><td><code>Natural32Value</code></td><td><code>Arcadia_Natural32Value</code></td></tr>
<tr><td><code>Natural64Value</code></td><td><code>Arcadia_Natural64Value</code></td></tr>
<tr><td><code>SizeValue</code></td><td><code>Arcadia_SizeValue</code></td></tr>
</table>

<h5>Parameters</h5>
<table>
  <tr><td>Arcadia_Thread* thread</td><td>A pointer to the <code>Arcadia_Thread</code> object.</td></tr>
  <tr><td><my-mv>Type</my-mv> x</td><td>The first value.</td></tr>
  <tr><td><my-mv>Type</my-mv> y</td><td>The second value.</td></tr>
</table>

<h5>Return value</h5>
<p>Return the maximum of <code>x</code> and <code>y</code>.</p>
