// Copyright (c) 2017
//
// Noctem / HatchingEgg
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
// EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
// OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONIN-
// FRINGEMENT.
// IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR
// ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
// TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE
// OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
// ---

#define PY_SSIZE_T_CLEAN

#include <Python.h>
#include "twofish.h"
#ifdef _WIN32
#include <malloc.h>
#endif

#define BLOCK_SIZE 16
#define INTEGRITY_BYTE 0x21
#define KEY_SIZE 32

Twofish_Byte enc_key[KEY_SIZE] = { // 1.29.1
    0x4F, 0xEB, 0x1C, 0xA5, 0xF6, 0x1A, 0x67, 0xCE, 0x43, 0xF3, 0xF0,
    0x0C, 0xB1, 0x23, 0x88, 0x35, 0xE9, 0x8B, 0xE8, 0x39, 0xD8, 0x89,
    0x8F, 0x5A, 0x3B, 0x51, 0x2E, 0xA9, 0x47, 0x38, 0xC4, 0x14,
};

static PyObject *pycrypt(PyObject *self, PyObject *args) {
  const char *input;
  Py_ssize_t len;
  uint32_t ms;

  if (!PyArg_ParseTuple(args, "y#I", &input, &len, &ms)) {
    return NULL;
  }

  uint32_t state = ms;

  Twofish_key key;
  Twofish_prepare_key(enc_key, KEY_SIZE, &key);

  uint8_t xor_byte[BLOCK_SIZE] = { 0, };
  for (int i = 0; i < BLOCK_SIZE; ++i) {
    state = (0x41C64E6D * state) + 0x3039;
    xor_byte[i] = (state >> 16) & 0x7FFF;
  }

  int block_count = (len + 256) / 256;
  int output_size = 4 + (block_count * 256) + 1;
#ifdef _WIN32
  uint8_t * output = (uint8_t *)_malloca( output_size );
#else
  uint8_t output[output_size];
#endif
  output[0] = (ms >> 24);
  output[1] = (ms >> 16);
  output[2] = (ms >> 8);
  output[3] = ms;
  memcpy(output + 4, input, len);
  memset(output + 4 + len, 0, 256 - len % 256);
  output[output_size - 2] = (uint8_t)(256 - len % 256);

  for (int offset = 0; offset < block_count * 256; offset += BLOCK_SIZE) {
    for (int i = 0; i < BLOCK_SIZE; i++)
      output[4 + offset + i] ^= xor_byte[i];

    Twofish_encrypt(&key, output + 4 + offset, output + 4 + offset);

    memcpy(xor_byte, output + 4 + offset, BLOCK_SIZE);
  }

  output[output_size - 1] = INTEGRITY_BYTE;

#ifdef _WIN32
  PyObject *output_bytes;
  output_bytes = PyBytes_FromStringAndSize((char *)output, output_size);
  _freea( output );
  return output_bytes;
#else
  return PyBytes_FromStringAndSize((char *)output, output_size);
#endif
}

/* List of functions defined in the module */
static PyMethodDef PycryptMethods[] = {
    {"pycrypt", pycrypt, METH_VARARGS, "TwoFish encryption."},
    {NULL, NULL, 0, NULL} /* sentinel */
};

static struct PyModuleDef pycryptmodule = {
    PyModuleDef_HEAD_INIT, "pycrypt", /* name of module */
    NULL,                             /* module documentation, may be NULL */
    -1,                               /* size of per-interpreter state of the module,
                                         or -1 if the module keeps state in global variables. */
    PycryptMethods};

PyMODINIT_FUNC PyInit_pycrypt(void) {
  Twofish_initialise();
  return PyModule_Create(&pycryptmodule);
}
