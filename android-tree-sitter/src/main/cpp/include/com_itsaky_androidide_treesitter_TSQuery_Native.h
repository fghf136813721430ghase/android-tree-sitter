/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
/* Header for class com_itsaky_androidide_treesitter_TSQuery_Native */

#ifndef _Included_com_itsaky_androidide_treesitter_TSQuery_Native
#define _Included_com_itsaky_androidide_treesitter_TSQuery_Native
#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     com_itsaky_androidide_treesitter_TSQuery_Native
 * Method:    newQuery
 * Signature: (Lcom/itsaky/androidide/treesitter/TSQuery;JLjava/lang/String;)J
 */
JNIEXPORT jlong JNICALL Java_com_itsaky_androidide_treesitter_TSQuery_00024Native_newQuery
  (JNIEnv *, jclass, jobject, jlong, jstring);

/*
 * Class:     com_itsaky_androidide_treesitter_TSQuery_Native
 * Method:    delete
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_com_itsaky_androidide_treesitter_TSQuery_00024Native_delete
  (JNIEnv *, jclass, jlong);

/*
 * Class:     com_itsaky_androidide_treesitter_TSQuery_Native
 * Method:    captureCount
 * Signature: (J)I
 */
JNIEXPORT jint JNICALL Java_com_itsaky_androidide_treesitter_TSQuery_00024Native_captureCount
  (JNIEnv *, jclass, jlong);

/*
 * Class:     com_itsaky_androidide_treesitter_TSQuery_Native
 * Method:    patternCount
 * Signature: (J)I
 */
JNIEXPORT jint JNICALL Java_com_itsaky_androidide_treesitter_TSQuery_00024Native_patternCount
  (JNIEnv *, jclass, jlong);

/*
 * Class:     com_itsaky_androidide_treesitter_TSQuery_Native
 * Method:    stringCount
 * Signature: (J)I
 */
JNIEXPORT jint JNICALL Java_com_itsaky_androidide_treesitter_TSQuery_00024Native_stringCount
  (JNIEnv *, jclass, jlong);

/*
 * Class:     com_itsaky_androidide_treesitter_TSQuery_Native
 * Method:    startByteForPattern
 * Signature: (JI)I
 */
JNIEXPORT jint JNICALL Java_com_itsaky_androidide_treesitter_TSQuery_00024Native_startByteForPattern
  (JNIEnv *, jclass, jlong, jint);

/*
 * Class:     com_itsaky_androidide_treesitter_TSQuery_Native
 * Method:    predicatesForPattern
 * Signature: (JI)[Lcom/itsaky/androidide/treesitter/TSQueryPredicateStep;
 */
JNIEXPORT jobjectArray JNICALL Java_com_itsaky_androidide_treesitter_TSQuery_00024Native_predicatesForPattern
  (JNIEnv *, jclass, jlong, jint);

/*
 * Class:     com_itsaky_androidide_treesitter_TSQuery_Native
 * Method:    patternRooted
 * Signature: (JI)Z
 */
JNIEXPORT jboolean JNICALL Java_com_itsaky_androidide_treesitter_TSQuery_00024Native_patternRooted
  (JNIEnv *, jclass, jlong, jint);

/*
 * Class:     com_itsaky_androidide_treesitter_TSQuery_Native
 * Method:    patternGuaranteedAtStep
 * Signature: (JI)Z
 */
JNIEXPORT jboolean JNICALL Java_com_itsaky_androidide_treesitter_TSQuery_00024Native_patternGuaranteedAtStep
  (JNIEnv *, jclass, jlong, jint);

/*
 * Class:     com_itsaky_androidide_treesitter_TSQuery_Native
 * Method:    captureNameForId
 * Signature: (JI)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_com_itsaky_androidide_treesitter_TSQuery_00024Native_captureNameForId
  (JNIEnv *, jclass, jlong, jint);

/*
 * Class:     com_itsaky_androidide_treesitter_TSQuery_Native
 * Method:    stringValueForId
 * Signature: (JI)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_com_itsaky_androidide_treesitter_TSQuery_00024Native_stringValueForId
  (JNIEnv *, jclass, jlong, jint);

#ifdef __cplusplus
}
#endif
#endif