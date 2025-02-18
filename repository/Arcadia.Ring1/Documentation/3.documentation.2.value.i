<h3 id="value-type">3.2. Value Type</h3>
<p>
<code>Arcadia_Value</code> is a tagged union of values supported by the
runtime. It consists of a tag indicating the value stored in the
union and the union of the values. The following table lists all
possible tags and their corresponding type.
</p>
<table>
  <tr><td>Tag                       </td><td>Type                  </td></tr>

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

  <tr><td>Arcadia_ValueTag_Size           </td><td>Arcadia_SizeValue           </td></tr>

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
  <tr><td>Boolean        </td><td>boolean        </td></tr>

  <tr><td>Integer16      </td><td>integer16      </td></tr>
  <tr><td>Integer32      </td><td>integer32      </td></tr>
  <tr><td>Integer64      </td><td>integer64      </td></tr>
  <tr><td>Integer8       </td><td>integer8       </td></tr>

  <tr><td>Natural16      </td><td>natural16      </td></tr>
  <tr><td>Natural32      </td><td>natural32      </td></tr>
  <tr><td>Natural64      </td><td>natural64      </td></tr>
  <tr><td>Natural8       </td><td>natural8       </td></tr>
  
  <tr><td>ObjectReference</td><td>objectReference</td></tr>

  <tr><td>Size           </td><td>size           </td></tr>

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
