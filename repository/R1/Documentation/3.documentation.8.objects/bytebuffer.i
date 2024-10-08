<h4 id="r-bytebuffer">Byte Buffer</h4>
<p>
<code>R_ByteBuffer</code> represents a mutable sequence of Bytes.
This type is allocated on the heap and values of this type are referenced by <code>R_ByteBuffer</code> pointers.
A <code>R_ByteBuffer</code> pointer can be safely cast into a <code>R_ObjectReferenceValue</code> values.
An <code>R_ObjectReferenceValue</code> pointing to a <code>R_ByteBuffer</code> value can be safely cast into a <code>R_ByteBuffer</code> pointer.
</p>

<!-- ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ -->
<h5 id="r-bytebuffer-create">create</h5>

<p><code>
R_ByteBuffer* R_ByteBuffer_create()
</code></p>

<p>Create an empty Byte buffer.</p>

<h6><b>Return Value</b></h6>
<p>A pointer to the Byte buffer.</p>

<!-- ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ -->
<h5 id="r-bytebuffer-clear">clear</h5>
<p><code>
void R_ByteBuffer_clear(R_ByteBuffer* self)
</code></p>

<p>Set the number of elements of this Byte buffer to zero.</p>

<h6><b>Parameters</b></h6>
<table>
  <tr><td>R_ByteBuffer* self</td><td>A pointer to this Byte buffer.</td></tr>
</table>

<!-- ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ -->

<h5 id="r-bytebuffer-endswith-pn">endsWith_pn</h5>
<p><code>
R_BooleanValue R_ByteBuffer_endsWith_pn(R_ByteBuffer const* self, void const* bytes, R_SizeValue numberOfBytes)
</code></p>

<p>Get if a sequence of Bytes is a suffix of this Byte buffer's sequence of Bytes.</p>

<h6><b>Parameters</b></h6>
<table>
  <tr><td>R_ByteBuffer* self       </td><td>A pointer to this Byte buffer.</td></tr>
  <tr><td>void const* bytes        </td><td>A pointer to an array of <code>n</code> Bytes.</td></tr>
  <tr><td>R_SizeValue numberOfBytes</td><td>The number of Bytes in the array pointed to by <code>p</code>.</td></tr>
</table>

<h6><b>Return Value</b></h6>
<p>
<code>R_BooleanValue_True</code> if the sequence of Bytes is a suffix of this byte buffer's sequence of Bytes.
<code>R_BooleanValue_False</code> otherwise.
</p>

<!-- ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ -->

<h5 id="r-bytebuffer-startswith-pn">startsWith_pn</h5>
<p><code>
R_BooleanValue R_ByteBuffer_startsWith_pn(R_ByteBuffer const* self, void const* bytes, R_SizeValue numberOfBytes)
</code></p>

<p>Get if a sequence of Bytes is a prefix of this Byte buffer's sequence of Bytes.</p>

<h6><b>Parameters</b></h6>
<table>
  <tr><td>R_ByteBuffer* self       </td><td>A pointer to this Byte buffer.</td></tr>
  <tr><td>void const* bytes        </td><td>A pointer to an array of <code>n</code> Bytes.</td></tr>
  <tr><td>R_SizeValue numberOfBytes</td><td>The number of Bytes in the array pointed to by <code>p</code>.</td></tr>
</table>

<h6><b>Return Value</b></h6>
<p>
<code>R_BooleanValue_True</code> if the sequence of Bytes is a prefix of this byte buffer's sequence of Bytes.
<code>R_BooleanValue_False</code> otherwise.
</p>


<!-- ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ -->

<h5 id="r-bytebuffer-isequalto-pn">isEqualTo_pn</h5>
<p><code>
R_BooleanValue R_ByteBuffer_isEqualTo_pn(R_ByteBuffer const* self, void const* bytes, R_SizeValue numberOfBytes)
</code></p>

<p>Get if a sequence of Bytes is this Byte buffer's sequence of Bytes.</p>

<h6><b>Parameters</b></h6>
<table>
  <tr><td>R_ByteBuffer* self       </td><td>A pointer to this Byte buffer.</td></tr>
  <tr><td>void const* bytes        </td><td>A pointer to an array of <code>n</code> Bytes.</td></tr>
  <tr><td>R_SizeValue numberOfBytes</td><td>The number of Bytes in the array pointed to by <code>p</code>.</td></tr>
</table>

<h6><b>Return Value</b></h6>
<p>
<code>R_BooleanValue_True</code> if the sequence of Bytes is this byte buffer's sequence of Bytes.
<code>R_BooleanValue_False</code> otherwise.
</p>

<!-- ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ -->
<h5 id="r-bytebuffer-append-pn">append_pn</h5>
<p><code>
void R_ByteBuffer_append_pn(R_ByteBuffer* self, void const* bytes, R_SizeValue numberOfBytes)
</code></p>

<p>Append Bytes to this Byte buffer.</p>

<h6><b>Parameters</b></h6>
<table>
  <tr><td>R_ByteBuffer* self       </td><td>A pointer to this Byte buffer.</td></tr>
  <tr><td>void const* bytes        </td><td>A pointer to an array of <code>n</code> Bytes.</td></tr>
  <tr><td>R_SizeValue numberOfBytes</td><td>The number of Bytes in the array pointed to by <code>p</code>.</td></tr>
</table>

<h6><b>Errors</b></h6>
<table>
  <tr><td>R_Status_ArgumentValueInvalid</td><td><code>self</code> is a null pointer. </td></tr>
  <tr><td>R_Status_ArgumentValueInvalid</td><td><code>bytes</code> is a null pointer.</td></tr>
  <tr><td>R_Status_AllocationFailed    </td><td>An allocation failed.                </td></tr>
</table>

<!-- ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ -->
<h5 id="r-bytebuffer-prepend-pn">prepend_pn</h5>
<p><code>
void R_ByteBuffer_prepend_pn(R_ByteBuffer* self, void const* p, R_SizeValue n)
</code></p>

<p>Prepend Bytes to this Byte buffer.</p>

<h6><b>Parameters</b></h6>
<table>
  <tr><td>R_ByteBuffer* self</td><td>A pointer to this Byte buffer.</td></tr>
  <tr><td>void const* p     </td><td>A pointer to an array of <code>n</code> Bytes.</td></tr>
  <tr><td>R_SizeValue n     </td><td>The number of Bytes in the array pointed to by <code>p</code>.</td></tr>
</table>

<h6><b>Errors</b></h6>
<table>
  <tr><td>R_Status_ArgumentValueInvalid</td><td><code>self</code> is a null pointer. </td></tr>
  <tr><td>R_Status_ArgumentValueInvalid</td><td><code>bytes</code> is a null pointer.</td></tr>
  <tr><td>R_Status_AllocationFailed    </td><td>An allocation failed.                </td></tr>
</table>

<!-- ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ -->
<h5 id="r-bytebuffer-insert-pn">insert_pn</h5>
<p><code>
void R_ByteBuffer_insert_pn(R_ByteBuffer* self, R_SizeValue index, void const* p, R_SizeValue n)
</code></p>

<p>Insert Bytes into this Byte buffer.</p>

<h6><b>Parameters</b></h6>
<table>
  <tr><td>R_ByteBuffer* self</td><td>A pointer to this Byte buffer.</td></tr>
  <tr><td>R_SizeValue index </td><td>The index at which to insert the Bytes. Must be within the bounds of <code>[0,n)</code> where <code>n</code> is the size of this Byte buffer.</td></tr>
  <tr><td>void const* p     </td><td>A pointer to an array of <code>n</code> Bytes.</td></tr>
  <tr><td>R_SizeValue n     </td><td>The number of Bytes in the array pointed to by <code>p</code>.</td></tr>
</table>

<h6><b>Errors</b></h6>
<table>
  <tr><td>R_Status_ArgumentValueInvalid</td><td><code>self</code> is a null pointer. </td></tr>
  <tr><td>R_Status_ArgumentValueInvalid</td><td><code>bytes</code> is a null pointer.</td></tr>
  <tr><td>R_Status_AllocationFailed    </td><td>An allocation failed.                </td></tr>
</table>

<!-- ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ -->
<h5 id="r-bytebuffer-isequalto">isEqualTo</h5>
<p><code>
R_BooleanValue R_ByteBuffer_isEqualTo(R_ByteBuffer const* self, R_ByteBuffer const* other)
</code></p>

<p>Compare this Byte buffer with another Byte buffer for equality.</p>

<h6><b>Parameters</b></h6>
<table>
  <tr><td>R_ByteBuffer const* self </td><td>A pointer to this Byte buffer.</td></tr>
  <tr><td>R_ByteBuffer const* other</td><td>A pointer to the other Byte buffer.</td></tr>
</table>

<h6><b>Return Value</b></h6>
<p>
<code>R_BooleanValue_True</code> if this Byte buffer is equal to the other Byte buffer.
<code>R_BooleanValue_False</code> otherwise.
</p>

<!-- ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ -->
<h5 id="r-bytebuffer-getsize">getSize</h5>
<p><code>
R_SizeValue R_ByteBuffer_getSize(R_ByteBuffer const* self)
</code></p>

<p>Get the size of this Byte buffer.</p>

<h6><b>Parameters</b></h6>
<table>
  <tr><td>R_ByteBuffer* self</td><td>A pointer to this Byte buffer.</td></tr>
</table>

<h6><b>Return Value</b></h6>
<p>The size of this Byte buffer.</p>

<h6><b>Remarks</b></h6>
<p> The size of a Byte buffer is the length of the Byte sequence it contains.</p>

<!-- ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ -->
<h5 id="r-bytebuffer-getat">getat</h5>
<p><code>
R_Natural8Value R_ByteBuffer_getAt(R_ByteBuffer const* self, R_SizeValue index)
</code></p>

<p>Get the Byte value at the specified index.</p>

<h6><b>Parameters</b></h6>
<table>
  <tr><td>R_ByteBuffer* self</td><td>A pointer to this Byte buffer.</td></tr>
  <tr><td>R_SizeValue index</td><td>The index. Must be within the bounds <code>[0,n)</code> where <code>n</code> is the size of this Byte buffer.</td></tr>
</table>

<h6><b>Return Value</b></h6>
<p>The Byte value.</p>

<h6><b>Remarks</b></h6>
<p> The size of a Byte buffer is the length of the Byte sequence it contains.</p>

<!-- ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ -->
<h5 id="r-bytebuffer-isempty">isEmpty</h5>
<p><code>
R_BooleanValue R_ByteBuffer_isEmpty(R_ByteBuffer* self)
</code></p>

<p>Get if this Byte buffer is empty.</p>

<h6><b>Parameters</b></h6>
<table>
  <tr><td>R_ByteBuffer* self</td><td>A pointer to this Byte buffer.</td></tr>
</table>

<h6><b>Return Value</b></h6>
<p><code>R_BooleanValue_True</code> if this Byte buffer is empty. <code>R_BooleanValue_False</code> otherwise.</p>

<h6><b>Errors</b></h6>
<table>
  <tr><td>R_Status_ArgumentValueInvalid</td><td><code>self</code> is a null pointer.</td></tr>
</table>

<!-- ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ -->
<h5 id="r-bytebuffer-swap">swap</h5>
<p><code>
void R_ByteBuffer_swap(R_ByteBuffer* self, R_ByteBuffer* other)
</code></p>

<p>Swap the contents of this Byte buffer with the contents of another Byte buffer.</p>

<h6><b>Parameters</b></h6>
<table>
  <tr><td>R_ByteBuffer* self</td><td>A pointer to this Byte buffer.</td></tr>
  <tr><td>R_ByteBuffer* self</td><td>A pointer to the other Byte buffer.</td></tr>
</table>

<h6><b>Errors</b></h6>
<table>
  <tr><td>R_Status_ArgumentValueInvalid</td><td><code>self</code> is a null pointer.</td></tr>
  <tr><td>R_Status_ArgumentValueInvalid</td><td><code>other</code> is a null pointer.</td></tr>
</table>
