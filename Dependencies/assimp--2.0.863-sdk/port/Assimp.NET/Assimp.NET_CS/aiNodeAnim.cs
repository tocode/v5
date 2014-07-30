/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 2.0.1
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */


using System;
using System.Runtime.InteropServices;

public class aiNodeAnim : IDisposable {
  private HandleRef swigCPtr;
  protected bool swigCMemOwn;

  internal aiNodeAnim(IntPtr cPtr, bool cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = new HandleRef(this, cPtr);
  }

  internal static HandleRef getCPtr(aiNodeAnim obj) {
    return (obj == null) ? new HandleRef(null, IntPtr.Zero) : obj.swigCPtr;
  }

  ~aiNodeAnim() {
    Dispose();
  }

  public virtual void Dispose() {
    lock(this) {
      if (swigCPtr.Handle != IntPtr.Zero) {
        if (swigCMemOwn) {
          swigCMemOwn = false;
          AssimpPINVOKE.delete_aiNodeAnim(swigCPtr);
        }
        swigCPtr = new HandleRef(null, IntPtr.Zero);
      }
      GC.SuppressFinalize(this);
    }
  }

  public aiVectorKeyVector mPositionKeys { get { return GetmPositionKeys(); } }
  public aiQuatKeyVector mRotationKeys { get { return GetmRotationKeys(); } }
  public aiVectorKeyVector mScalingKeys { get { return GetmScalingKeys(); } }

  public aiString mNodeName {
    set {
      AssimpPINVOKE.aiNodeAnim_mNodeName_set(swigCPtr, aiString.getCPtr(value));
    } 
    get {
      IntPtr cPtr = AssimpPINVOKE.aiNodeAnim_mNodeName_get(swigCPtr);
      aiString ret = (cPtr == IntPtr.Zero) ? null : new aiString(cPtr, false);
      return ret;
    } 
  }

  public uint mNumPositionKeys {
    set {
      AssimpPINVOKE.aiNodeAnim_mNumPositionKeys_set(swigCPtr, value);
    } 
    get {
      uint ret = AssimpPINVOKE.aiNodeAnim_mNumPositionKeys_get(swigCPtr);
      return ret;
    } 
  }

  public uint mNumRotationKeys {
    set {
      AssimpPINVOKE.aiNodeAnim_mNumRotationKeys_set(swigCPtr, value);
    } 
    get {
      uint ret = AssimpPINVOKE.aiNodeAnim_mNumRotationKeys_get(swigCPtr);
      return ret;
    } 
  }

  public uint mNumScalingKeys {
    set {
      AssimpPINVOKE.aiNodeAnim_mNumScalingKeys_set(swigCPtr, value);
    } 
    get {
      uint ret = AssimpPINVOKE.aiNodeAnim_mNumScalingKeys_get(swigCPtr);
      return ret;
    } 
  }

  public aiAnimBehaviour mPreState {
    set {
      AssimpPINVOKE.aiNodeAnim_mPreState_set(swigCPtr, (int)value);
    } 
    get {
      aiAnimBehaviour ret = (aiAnimBehaviour)AssimpPINVOKE.aiNodeAnim_mPreState_get(swigCPtr);
      return ret;
    } 
  }

  public aiAnimBehaviour mPostState {
    set {
      AssimpPINVOKE.aiNodeAnim_mPostState_set(swigCPtr, (int)value);
    } 
    get {
      aiAnimBehaviour ret = (aiAnimBehaviour)AssimpPINVOKE.aiNodeAnim_mPostState_get(swigCPtr);
      return ret;
    } 
  }

  public aiNodeAnim() : this(AssimpPINVOKE.new_aiNodeAnim(), true) {
  }

  private aiVectorKeyVector GetmPositionKeys() {
    IntPtr cPtr = AssimpPINVOKE.aiNodeAnim_GetmPositionKeys(swigCPtr);
    aiVectorKeyVector ret = (cPtr == IntPtr.Zero) ? null : new aiVectorKeyVector(cPtr, true);
    return ret;
  }

  private aiQuatKeyVector GetmRotationKeys() {
    IntPtr cPtr = AssimpPINVOKE.aiNodeAnim_GetmRotationKeys(swigCPtr);
    aiQuatKeyVector ret = (cPtr == IntPtr.Zero) ? null : new aiQuatKeyVector(cPtr, true);
    return ret;
  }

  private aiVectorKeyVector GetmScalingKeys() {
    IntPtr cPtr = AssimpPINVOKE.aiNodeAnim_GetmScalingKeys(swigCPtr);
    aiVectorKeyVector ret = (cPtr == IntPtr.Zero) ? null : new aiVectorKeyVector(cPtr, true);
    return ret;
  }

}
