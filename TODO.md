### dtk

* **Export rules**

  Export rules have not been backported or implemented yet. They are
  to be added on a use case basis, for each function that not to be
  used. Do not export classes as a whole.

### dtkComposer

* Proofread use of dtkLog layer

* Handle layer related nodes, e.g. dtkComposerNodeRemote

### dtk3D

* Qt 5.1.0 adds geometry shader support (QOpenGLShaderProgram). Update
  dtkEffect item accordingly or drop it whenever Qt3D is ready.

