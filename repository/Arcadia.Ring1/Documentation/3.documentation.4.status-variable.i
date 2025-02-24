  <h3 id="status-variable">3.4. Status Variable</h3>
  <p>R provides a global status variable.</p>

  <p><code>
  R_Status
  R_getStatus
    (
    );
  </code></p>
  <p>gets the value of the status variable. The initial value of the status variable is <code>Arcadia_Status_Success</code>.</p>

  <p><code>
  void
  Arcadia_Process_setStatus
    (
      Arcadia_Process* process,
      Arcadia_Status status
    );
  </code></p>
  <p>sets the value of the status variable to the value <code>status</code>.</p>
