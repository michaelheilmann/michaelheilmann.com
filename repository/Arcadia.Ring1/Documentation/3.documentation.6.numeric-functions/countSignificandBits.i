<h4 id="Arcadia_countSignificandBits*">Arcadia_countSignificandBits*</h4>
<p>Return the number of significand Bits of the binary representation of a value.</p>
<p><code>
Arcadia_SizeValue
Arcadia_countSignificandBits<my-mv>Suffix</my-mv>
  (
    Arcadia_Thread* thread,
    <my-mv>Type</my-mv> value
  )
</code></p>
<p>The following table lists the combinations of <my-mv>Type</my-mv> and <my-mv>Suffix</my-mv> for which the above functions are defined</p>

<table>
<tr><td><my-mv>Suffix</my-mv></td><td><my-mv>Type</my-mv></td></tr>
<tr><td><code>Integer8Value</code>  </td><td><code>Arcadia_Integer8Value</code></td></tr>
<tr><td><code>Integer16Value</code> </td><td><code>Arcadia_Integer16Value</code></td></tr>
<tr><td><code>Integer32Value</code> </td><td><code>Arcadia_Integer32Value</code></td></tr>
<tr><td><code>Integer64Value</code> </td><td><code>Arcadia_Integer64Value</code></td></tr>
<tr><td><code>Natural8Value</code>  </td><td><code>Arcadia_Natural8Value</code></td></tr>
<tr><td><code>Natural16Value</code> </td><td><code>Arcadia_Natural16Value</code></td></tr>
<tr><td><code>Natural32Value</code> </td><td><code>Arcadia_Natural32Value</code></td></tr>
<tr><td><code>Natural64Value</code> </td><td><code>Arcadia_Natural64Value</code></td></tr>
<tr><td><code>SizeValue</code>      </td><td><code>Arcadia_SizeValue</code></td></tr>
</table>

<p>This function returns the number of significand Bits of the binary representation of <code>value</code>.</p>

<h5>Parameters</h5>
<table>
  <tr><td>Arcadia_Thread* thread</td><td>A pointer to the <code>Arcadia_Thread</code> object.</td></tr>
  <tr><td><my-mv>Type</my-mv> value</td><td>The value.</td></tr>
</table>

<h5>Return value</h5>
<p>The number of significand Bits.</p>
