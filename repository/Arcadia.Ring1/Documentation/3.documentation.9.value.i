<h3 id="Arcadia_Value">Arcadia_Value</h3>
<p>
<code>Arcadia_Value</code> is a tagged union of values supported by the
runtime. It consists of a tag indicating the value stored in the
union and the union of the values. The following table lists all
possible tags and their corresponding type.
</p>
<table>
  <tr><td>Tag                             </td><td>Type                        </td></tr>
  <tr><td>Arcadia_ValueTag_Atom n         </td><td>Arcadia_AtomValue           </td></tr>
  <tr><td>Arcadia_ValueTag_Boolean        </td><td>Arcadia_BooleanValue        </td></tr>

  <tr><td>Arcadia_ValueTag_Integer16      </td><td>Arcadia_Integer16Value      </td></tr>
  <tr><td>Arcadia_ValueTag_Integer32      </td><td>Arcadia_Integer32Value      </td></tr>
  <tr><td>Arcadia_ValueTag_Integer64      </td><td>Arcadia_Integer64Value      </td></tr>
  <tr><td>Arcadia_ValueTag_Integer8       </td><td>Arcadia_Integer8Value       </td></tr>

  <tr><td>Arcadia_ValueTag_Natural16      </td><td>Arcadia_Natural16Value      </td></tr>
  <tr><td>Arcadia_ValueTag_Natural32      </td><td>Arcadia_Natural32Value      </td></tr>
  <tr><td>Arcadia_ValueTag_Natural64      </td><td>Arcadia_Natural64Value      </td></tr>
  <tr><td>Arcadia_ValueTag_Natural8       </td><td>Arcadia_Natural8Value       </td></tr>

  <tr><td>Arcadia_ValueTag_ObjectReference</td><td>Arcadia_ObjectReferenceValue</td></tr>

  <tr><td>Arcadia_ValueTag_Real32         </td><td>Arcadia_Real32Value         </td></tr>
  <tr><td>Arcadia_ValueTag_Real64         </td><td>Arcadia_Real64Value         </td></tr>

  <tr><td>Arcadia_ValueTag_Size           </td><td>Arcadia_SizeValue           </td></tr>

  <tr><td>Arcadia_ValueTag_Type           </td><td>Arcadia_TypeValue           </td></tr>

  <tr><td>Arcadia_ValueTag_Void           </td><td>Arcadia_VoidValue           </td></tr>
</table>

<p>
For each type, <code>Arcadia_Value</code> has three functions associated:
</p>
<p><code>
<my-mv>Type</my-mv> Arcadia_Value_get<my-mv>Suffix</my-mv>(Arcadia_Value const* value)<br>
bool Arcadia_Value_is<my-mv>Suffix</my-mv>(Arcadia_Value const* value)<br>
void Arcadia_Value_set<my-mv>Suffix</my-mv>(Arcadia_Value* value, Arcadia_<my-mv>Suffix</my-mv>Value <my-mv>Variable</my-mv>Value)
</code></p>
<p>The following table lists the valid combinations of <my-mv>Suffix</my-mv> and <my-mv>Variable</my-mv></p>

<table>
  <tr><td>Atom           </td><td>atom           </td></tr>
  <tr><td>Boolean        </td><td>boolean        </td></tr>

  <tr><td>Integer16      </td><td>integer16      </td></tr>
  <tr><td>Integer32      </td><td>integer32      </td></tr>
  <tr><td>Integer64      </td><td>integer64      </td></tr>
  <tr><td>Integer8       </td><td>integer8       </td></tr>

  <tr><td>Natural16      </td><td>natural16      </td></tr>
  <tr><td>Natural32      </td><td>natural32      </td></tr>
  <tr><td>Natural64      </td><td>natural64      </td></tr>
  <tr><td>Natural8       </td><td>natural8       </td></tr>

  <tr><td>Real32         </td><td>reall32        </td></tr>
  <tr><td>Real64         </td><td>real64         </td></tr>
  
  <tr><td>ObjectReference</td><td>objectReference</td></tr>

  <tr><td>Size           </td><td>size           </td></tr>

  <tr><td>Type           </td><td>type           </td></tr>

  <tr><td>Void           </td><td>void           </td></tr>
</table>

<p><code>Arcadia_Value_is<my-mv>Suffix</my-mv></code> returns <code>true</code> if
the <code>Arcadia_Value</code> stores a value of the type corresponding to <my-mv>Suffix</my-mv>. Otherwise it returns <code>false</code>.</p>

<p><code>Arcadia_Value_set<my-mv>Suffix</my-mv></code> assigns the <code>Arcadia_Value</code>
a value of the type corresponding to <my-mv>Suffix</my-mv>.</p>

<p><code>Arcadia_Value_get<my-mv>Type</my-mv></code> get the value stored   in
the <code>Arcadia_Value</code>. The behavior of <code>Arcadia_Value_set<my-mv>Suffix
</my-mv></code> is undefined if the value does not store a value of  the
type corresponding to <my-mv>Suffix</my-mv>.</p>




<h4>hash</h4>
<p><code>
Arcadia_Size
Arcadia_Value_hash
  (
    Arcadia_Process* process,
    Arcadia_Value* self
  );
</code></p>
<p>Get the hash value of this <code>Arcadia_Value</code>.</p>

<h5>Parameters</h5>
<table>
  <tr><td>process</td><td>A pointer to the <code>Arcadia_Process</code> object.</td></tr>
  <tr><td>self</td><td>A pointer to this <code>Arcadia_Value</code> object.</td></tr>
</table>

<h5>Return value</h5>
<p>The hash of the value of the value of this<code>Arcadia_Value</code> object.</p>




<h4>isEqualTo</h4>
<p><code>
Arcadia_BooleanValue
Arcadia_Value_isEqualTo
  (
    Arcadia_Process* process,
    Arcadia_Value* self,
    Arcadia_Value* other
  );
</code></p>
<p>Compare the value of this <code>Arcadia_Value</code> object to the value of another <code>Arcadia_Value</code> object.</p>

<h5>Parameters</h5>
<table>
  <tr><td>process</td><td>A pointer to the <code>Arcadia_Process</code> object.</td></tr>
  <tr><td>self</td><td>A pointer to this <code>Arcadia_Value</code> object.</td></tr>
  <tr><td>object</td><td>A pointer to the other <code>Arcadia_Value</code> object.</td></tr>
</table>

<h5>Return value</h5>
<p>
<code>Arcadia_BooleanValue_True</code> if the value of this <code>Arcadia_Value</code> object is equal to the value of the other <code>Arcadia_Value</code> object.
<code>Arcadia_BooleanValue_False</code> otherwise.
</p>



<h4>isEqualTo</h4>
<p><code>
Arcadia_TypeValue
Arcadia_Value_isEqualTo
  (
    Arcadia_Process* process,
    Arcadia_Value* self
  );
</code></p>
<p>Get thet type of the value of this <code>Arcadia_Value</code> object.</p>

<h5>Parameters</h5>
<table>
  <tr><td>process</td><td>A pointer to the <code>Arcadia_Process</code> object.</td></tr>
  <tr><td>self</td><td>A pointer to this <code>Arcadia_Value</code> object.</td></tr>
 </table>

<h5>Return value</h5>
<p>
The type of the value of this <code>Arcadia_Value</code> object.
</p>
