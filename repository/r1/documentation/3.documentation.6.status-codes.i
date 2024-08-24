  <h3>Status Codes</h3>
  <p>
  R provides a status type and symbolic constants for its values. That type denotes success or failure of program (or a part of it)
  as well as information on the reason for the failure.</p>

  <p><code>
  typedef <my-mv>implementation detail</my-mv> R_Status
  </code></p>
  <p>
  <code>R_Status</code> is a natural number type of a width of 32 Bit.</p>

  <p><code>
  #definer R_Status_Success <my-mv>implementation detail</my-mv>
  </code></p>
  <p>is the symbolic constant of the type <code>R_Status</code> has the value <code>((R_Status)0)</code>.
  It denotes success and is guaranteed to be defined to the value <code>0</code> of the underlaying natural number
  type of R_Status as well as to be the only symbolic constant starting with <code>R_Status_</code> having
  defined to that value.</p>

  <p>
  Symbolic constants of the form
  </p>
  <p><code>
  #definer R_Status_<my-mv>Name</my-mv> <my-mv>implementation detail</my-mv>
  </code></p>
  <p>where <my-mv>Name</my-mv> is not <code>Success</code> provide information on failure of a program (or a part of it).
  The following table denotes the value of the constant for the respective <my-mv>Name</my-mv>
  </p>
  <table>
  <tr><td><code><span>Name</span></code>        </td><td>Value</td></tr>
  <tr><td><code>AllocationFailed</code>         </td><td>An allocation failed.</td></tr>
  <tr><td><code>ArgumentTypeInvalid</code>      </td><td>The type of an argument is invalid.</td></tr>
  <tr><td><code>ArgumentValueInvalid</code>     </td><td>The value of an argument is invalid.</td></tr>
  <tr><td><code>FileSystemOperationFailed</code></td><td>A file system operation failed.</td></tr>  
  
  
  <tr><td><code>Initialized</code>              </td><td>Something was initialized (but should not have been initialized).</td></tr>
  <tr><td><code>NumberOfArgumentsInvalid</code> </td><td>The number of arguments is invalid.</td></tr>
  <tr><td><code>OperationInvalid</code>         </td><td>An operation is invalid.</td></tr>
  <tr><td><code>TestFailed</code>               </td><td>A test failed. This is used by the built-in tests that ensure correctness.</td></tr>
  <tr><td><code>Uninitialized</code>            </td><td>Something was uninitialized (but should have been initialized).</td></tr>
  </table>
