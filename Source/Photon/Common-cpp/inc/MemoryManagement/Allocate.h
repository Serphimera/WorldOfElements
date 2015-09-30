/* Exit Games Common - C++ Client Lib
 * Copyright (C) 2004-2015 by Exit Games GmbH. All rights reserved.
 * http://www.exitgames.com
 * mailto:developer@exitgames.com
 */

#pragma once

#include <new>
#include "Common-cpp/inc/MemoryManagement/Internal/Interface.h"

#ifdef _EG_WINDOWS_PLATFORM
#	pragma push_macro("new")
#	undef new
#endif

/** @file */

/** @name LowLevelMemoryManagement
   @anchor LowLevelMemoryManagement
   The macros in this section are an alternative for the C dynamic memory management functions malloc(), free(), realloc() and calloc().
   They only work in C++, not in C, but same as the standard c library functions they don't call constructors/destructors, but only
   (de-)allocate the raw memory. This might be desired for high performance container implementations: it makes it possible to allocate
   storage for a lot of elements at once, while still giving the option to wait with construction until an element is actually first used.
   
   However in by far the most usage scenarios it makes more sense to use the
   @ref HighLevelMemoryManagement "High Level memory management functions"
   
   The Memory Management API is optimized for frequent small-sized general purpose dynamic allocations (all dynamic memory
   allocations that are smaller than several megabytes per allocation and that can happen inside the main loop). The concrete implementation
   may vary between platforms and configurations, but will usually be by multiple magnitudes faster for this purpose than the standard C
   functions malloc(), free(), realloc() and calloc() and the standard C++ operators new, new[], delete and delete[].*/
/*@{*/

/** @def EG_MALLOC
   This macro allocates the requested amount of bytes as a single continuous block from dynamic memory and returns the address of the
   first byte of that block.
   @details
   Blocks of memory that have been allocated with EG_MALLOC(), have to be deallocated with EG_FREE(), when they are no longer
   needed.
   
   If the requested amount of bytes is 0, then this macro will do nothing but returning a NULL pointer.*/
#define EG_MALLOC  ExitGames::Common::MemoryManagement::Internal::Interface::malloc

/** @def EG_FREE
   Pass the address of memory, that has previously been returned by EG_MALLOC(), EG_REALLOC() or EG_CALLOC() to this function, to deallocate it.
   @details
   If the passed address is NULL, then this macro will do nothing.

   If a passed non-NULL address has not previously been returned by EG_MALLOC(), EG_REALLOC() or EG_CALLOC(), then the behavior is undefined. */
#define EG_FREE    ExitGames::Common::MemoryManagement::Internal::Interface::free

/** @def EG_REALLOC
   This macro resizes the block of memory at the passed address to the passed size and returns the new address of this block of memory.
   @details
   The returned address isn't guaranteed to match the passed one. Depending on the exact old and new size of the memory block, resizing
   the block may include moving it to a new location. When exactly a block gets moved, is an implementation detail, that could be
   different between implementations on different platforms and can be changed without notice. Especially block-movements can't only
   happen, when the block size in-, but also when it decreases.

   If a block of memory gets moved to a new location, then the content of all bytes that fit in both, the old and the new block size,
   is copied from the old to the new location by a call to memcpy(). Therefor calls to EG_REALLOC() can be expensive for huge blocks of
   memory.

   If the new block size is smaller than the old one, then all content at the surplus bytes will get lost.

   If the passed address is NULL, then this macro will behave just like EG_MALLOC().

   If a passed non-NULL address has not previously been returned by EG_MALLOC(), EG_REALLOC() or EG_CALLOC(), then the behavior is undefined. */
#define EG_REALLOC ExitGames::Common::MemoryManagement::Internal::Interface::realloc

/** @def EG_CALLOC
   This macro allocates memory for the requested amount of array elements of the specified element size as a single continuous block
   from dynamic memory, initializes all its bytes to 0 and returns the address of the first byte of that block.
   @details
   Blocks of memory that have been allocated with EG_CALLOC(), have to be deallocated with EG_FREE(), when they are no longer
   needed.
   
   If the requested amount of bytes is 0, then this macro will do nothing but returning a NULL pointer.*/
#define EG_CALLOC ExitGames::Common::MemoryManagement::Internal::Interface::calloc


/*@}*/

namespace ExitGames
{
	namespace Common
	{
		namespace MemoryManagement
		{
			/** @name HighLevelMemoryManagement
			   @anchor HighLevelMemoryManagement 
			   The template functions in this section are an alternative for the C++ dynamic memory management operators new, new[],
			   delete and delete[].
			   They are implemented in terms of enhancing the @ref LowLevelMemoryManagement "Low Level Memory Management macros" and
			   therefor offer similar advantages over new and co like those macros offer over malloc and co, but same as new and co also
			   construct and destruct the objects, that they allocate and deallocate. */
			/*@{*/
			/**
			   This is the macro version of the allocate() template function.
			   @details
			   Normally the template version should be preferred, but using the macro instead can be needed, if you want to pass more
			   than 10 parameters to the constructor or if you want to call a private or protected constructor to which your class has
			   (friend-/subclass-)access.
			   @param type the data type of the instance to create
			   @param p a pointer, in which the macro will store the address of the freshly created instance
			   @param ... optional arguments to pass to the constructor */
#			define ALLOCATE(type, p, ...) (p = reinterpret_cast<type*>(EG_MALLOC(sizeof(type))), new(p) type(__VA_ARGS__))
			
			/**
			   This is the macro version of the allocateArray() template function.
			   @details
			   Normally the template version should be preferred, but using the macro instead can be needed, if you want to pass more
			   than 10 parameters to the constructor or if you want to call a private or protected constructor to which your class has
			   (friend-/subclass-)access.
			   @param type the data type of the instance to create
			   @param p a pointer, in which the macro will store the address of the freshly created instance
			   @param count the number of the elements to create
			   @param ... optional arguments to pass to the constructor */
#			define ALLOCATE_ARRAY(type, p, count, ...) p = reinterpret_cast<type*>(reinterpret_cast<size_t*>(EG_MALLOC(sizeof(type)*count+sizeof(size_t)))+1); *(reinterpret_cast<size_t*>(p)-1) = count; for(size_t i=0; i<count; ++i) ::new(p+i) type(__VA_ARGS__);
			
			/**
			   This is the macro version of the reallocateArray() template function.
			   @details
			   Normally the template version should be preferred, but using the macro instead can be needed, if you want to pass more
			   than 10 parameters to the constructor or if you want to call a private or protected constructor to which your class has
			   (friend-/subclass-)access.
			   @param type the data type of the instance to create
			   @param p a pointer, in which the macro will store the address of the freshly created instance
			   @param count the number of the elements to create
			   @param ... optional arguments to pass to the constructor */
#			define REALLOCATE_ARRAY(type, p, count, ...) {Ftype* pOut; size_t oldCount = p?*(reinterpret_cast<size_t*>(const_cast<Ftype*>(p))-1):0; pOut = reinterpret_cast<Ftype*>(reinterpret_cast<size_t*>(EG_MALLOC(sizeof(Ftype)*count+sizeof(size_t)))+1); *(reinterpret_cast<size_t*>(pOut)-1) = count; for(size_t i=0; i<oldCount && i<count; ++i) new(pOut+i) Ftype(p[i]); for(size_t i=oldCount; i<count; ++i) new(pOut+i) Ftype(__VA_ARGS__); DEALLOCATE_ARRAY(Ftype, p); p = pOut; return p;}

			/**
			   This is the macro version of the deallocate() template function.
			   @details
			   Normally the template version should be preferred, but using the macro instead can make sense for consistency reasons when
			   the macro version has been used for allocation.
			   @param type the data type of the instance, to which p points
			   @param p a pointer to the instance to destroy */
#			define DEALLOCATE(type, p) if(p){p->~type(); EG_FREE(const_cast<type*>(p));}

			/**
			   This is the macro version of the deallocateArray() template function.
			   @details
			   Normally the template version should be preferred, but using the macro instead can make sense for consistency reasons when
			   the macro version has been used for allocation.
			   @param type the data type of the instance, to which p points
			   @param p a pointer to the instance to destroy */
#			define DEALLOCATE_ARRAY(type, p) if(p){size_t* pRaw = (reinterpret_cast<size_t*>(const_cast<type*>(p))-1); for(size_t i=*pRaw; i-->0;) p[i].~type(); EG_FREE(pRaw);}

			/** @cond */
#			define ALLOCATE_TEMPLATE_BODY(...) Ftype* p; ALLOCATE(Ftype, p, __VA_ARGS__); return p;
#			define ALLOCATE_ARRAY_TEMPLATE_BODY(count, ...) Ftype* p; ALLOCATE_ARRAY(Ftype, p, count, __VA_ARGS__); return p;
#			define REALLOCATE_ARRAY_TEMPLATE_BODY(p, count, ...) REALLOCATE_ARRAY(Ftype, p, count, __VA_ARGS__); return p;
			/** @endcond */

			/**
			   This function allocates a new instance of the type, that has been specified as first template parameter, on dynamic memory
			   and properly initializes it. For an instance of a class type this includes calling a constructor on the instance.
			   @details
			   Instances, that have been allocated with allocate(), have to be deallocated with deallocate(), when they are no longer
			   needed.

			   Up to 10 optional arguments can be passed to allocate() and allocate() will call a constructor with the matching number of
			   parameters and matching parameter types. If the class of the object that is to be constructed, doesn't provide a
			   constructor with a matching signature, if that constructor isn't publicly accessible or if it is ambiguous, which
			   constructor to choose, then the call to allocate() will trigger an error from the compiler..

			   The allocation is implemented via a call to EG_MALLOC(). */
			template<typename Ftype>                                                                                                                                    Ftype* allocate(void)                                                                             {ALLOCATE_TEMPLATE_BODY()}
			/** @cond */ 
			template<typename Ftype, typename P1>                                                                                                                       Ftype* allocate(P1& p1)                                                                           {ALLOCATE_TEMPLATE_BODY(p1)}
			template<typename Ftype, typename P1, typename P2>                                                                                                          Ftype* allocate(P1& p1, P2& p2)                                                                   {ALLOCATE_TEMPLATE_BODY(p1, p2)}
			template<typename Ftype, typename P1, typename P2, typename P3>                                                                                             Ftype* allocate(P1& p1, P2& p2, P3& p3)                                                           {ALLOCATE_TEMPLATE_BODY(p1, p2, p3)}
			template<typename Ftype, typename P1, typename P2, typename P3, typename P4>                                                                                Ftype* allocate(P1& p1, P2& p2, P3& p3, P4& p4)                                                   {ALLOCATE_TEMPLATE_BODY(p1, p2, p3, p4)}
			template<typename Ftype, typename P1, typename P2, typename P3, typename P4, typename P5>                                                                   Ftype* allocate(P1& p1, P2& p2, P3& p3, P4& p4, P5& p5)                                           {ALLOCATE_TEMPLATE_BODY(p1, p2, p3, p4, p5)}
			template<typename Ftype, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6>                                                      Ftype* allocate(P1& p1, P2& p2, P3& p3, P4& p4, P5& p5, P6& p6)                                   {ALLOCATE_TEMPLATE_BODY(p1, p2, p3, p4, p5, p6)}
			template<typename Ftype, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7>                                         Ftype* allocate(P1& p1, P2& p2, P3& p3, P4& p4, P5& p5, P6& p6, P7& p7)                           {ALLOCATE_TEMPLATE_BODY(p1, p2, p3, p4, p5, p6, p7)}
			template<typename Ftype, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8>                            Ftype* allocate(P1& p1, P2& p2, P3& p3, P4& p4, P5& p5, P6& p6, P7& p7, P8& p8)                   {ALLOCATE_TEMPLATE_BODY(p1, p2, p3, p4, p5, p6, p7, p8)}
			template<typename Ftype, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8, typename P9>               Ftype* allocate(P1& p1, P2& p2, P3& p3, P4& p4, P5& p5, P6& p6, P7& p7, P8& p8, P9& p9)           {ALLOCATE_TEMPLATE_BODY(p1, p2, p3, p4, p5, p6, p7, p8, p9)}
			template<typename Ftype, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8, typename P9, typename P10> Ftype* allocate(P1& p1, P2& p2, P3& p3, P4& p4, P5& p5, P6& p6, P7& p7, P8& p8, P9& p9, P10& p10) {ALLOCATE_TEMPLATE_BODY(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10)}

			template<typename Ftype, typename P1>                                                                                                                       Ftype* allocate(const P1& p1)                                                                                                                                 {ALLOCATE_TEMPLATE_BODY(p1)}
			template<typename Ftype, typename P1, typename P2>                                                                                                          Ftype* allocate(const P1& p1, const P2& p2)                                                                                                                   {ALLOCATE_TEMPLATE_BODY(p1, p2)}
			template<typename Ftype, typename P1, typename P2, typename P3>                                                                                             Ftype* allocate(const P1& p1, const P2& p2, const P3& p3)                                                                                                     {ALLOCATE_TEMPLATE_BODY(p1, p2, p3)}
			template<typename Ftype, typename P1, typename P2, typename P3, typename P4>                                                                                Ftype* allocate(const P1& p1, const P2& p2, const P3& p3, const P4& p4)                                                                                       {ALLOCATE_TEMPLATE_BODY(p1, p2, p3, p4)}
			template<typename Ftype, typename P1, typename P2, typename P3, typename P4, typename P5>                                                                   Ftype* allocate(const P1& p1, const P2& p2, const P3& p3, const P4& p4, const P5& p5)                                                                         {ALLOCATE_TEMPLATE_BODY(p1, p2, p3, p4, p5)}
			template<typename Ftype, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6>                                                      Ftype* allocate(const P1& p1, const P2& p2, const P3& p3, const P4& p4, const P5& p5, const P6& p6)                                                           {ALLOCATE_TEMPLATE_BODY(p1, p2, p3, p4, p5, p6)}
			template<typename Ftype, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7>                                         Ftype* allocate(const P1& p1, const P2& p2, const P3& p3, const P4& p4, const P5& p5, const P6& p6, const P7& p7)                                             {ALLOCATE_TEMPLATE_BODY(p1, p2, p3, p4, p5, p6, p7)}
			template<typename Ftype, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8>                            Ftype* allocate(const P1& p1, const P2& p2, const P3& p3, const P4& p4, const P5& p5, const P6& p6, const P7& p7, const P8& p8)                               {ALLOCATE_TEMPLATE_BODY(p1, p2, p3, p4, p5, p6, p7, p8)}
			template<typename Ftype, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8, typename P9>               Ftype* allocate(const P1& p1, const P2& p2, const P3& p3, const P4& p4, const P5& p5, const P6& p6, const P7& p7, const P8& p8, const P9& p9)                 {ALLOCATE_TEMPLATE_BODY(p1, p2, p3, p4, p5, p6, p7, p8, p9)}
			template<typename Ftype, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8, typename P9, typename P10> Ftype* allocate(const P1& p1, const P2& p2, const P3& p3, const P4& p4, const P5& p5, const P6& p6, const P7& p7, const P8& p8, const P9& p9, const P10& p10) {ALLOCATE_TEMPLATE_BODY(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10)}
			/** @endcond */
			
			/**
			   This function allocates an array of new instances of the type, that has been specified as first template parameter, on
			   dynamic memory and properly initializes all of them. For arrays of class types this includes constructing each element via
			   a constructor with matching parameter list.
			   @details
			   Instances, that have been allocated with allocateArray(), have to be deallocated with deallocateArray(), when they are no
			   longer needed.

			   The passed element count is allowed to be 0. In that case this function still allocates storage to store the element count
			   of 0 in, so the returned address still has to be deallocated later.

			   Up to 10 optional arguments can be passed to allocateArray() and allocateArray() will call a constructor with the matching
			   number of parameters and matching parameter types. If the class of the elements that are to be constructed, doesn't provide
			   a constructor with a matching signature, if that constructor isn't publicly accessible or if it is ambiguous, which
			   constructor to choose, then the call to allocateArray() will trigger an error from the compiler.

			   The allocation is implemented via a call to EG_MALLOC().
			   @param count the amount of elements that the new array should have */
			template<typename Ftype>                                                                                                                                    Ftype* allocateArray(size_t count)                                                                                   {ALLOCATE_ARRAY_TEMPLATE_BODY(count)}
			/** @cond */ 
			template<typename Ftype, typename P1>                                                                                                                       Ftype* allocateArray(size_t count, P1& p1)                                                                           {ALLOCATE_ARRAY_TEMPLATE_BODY(count, p1)}
			template<typename Ftype, typename P1, typename P2>                                                                                                          Ftype* allocateArray(size_t count, P1& p1, P2& p2)                                                                   {ALLOCATE_ARRAY_TEMPLATE_BODY(count, p1, p2)}
			template<typename Ftype, typename P1, typename P2, typename P3>                                                                                             Ftype* allocateArray(size_t count, P1& p1, P2& p2, P3& p3)                                                           {ALLOCATE_ARRAY_TEMPLATE_BODY(count, p1, p2, p3)}
			template<typename Ftype, typename P1, typename P2, typename P3, typename P4>                                                                                Ftype* allocateArray(size_t count, P1& p1, P2& p2, P3& p3, P4& p4)                                                   {ALLOCATE_ARRAY_TEMPLATE_BODY(count, p1, p2, p3, p4)}
			template<typename Ftype, typename P1, typename P2, typename P3, typename P4, typename P5>                                                                   Ftype* allocateArray(size_t count, P1& p1, P2& p2, P3& p3, P4& p4, P5& p5)                                           {ALLOCATE_ARRAY_TEMPLATE_BODY(count, p1, p2, p3, p4, p5)}
			template<typename Ftype, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6>                                                      Ftype* allocateArray(size_t count, P1& p1, P2& p2, P3& p3, P4& p4, P5& p5, P6& p6)                                   {ALLOCATE_ARRAY_TEMPLATE_BODY(count, p1, p2, p3, p4, p5, p6)}
			template<typename Ftype, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7>                                         Ftype* allocateArray(size_t count, P1& p1, P2& p2, P3& p3, P4& p4, P5& p5, P6& p6, P7& p7)                           {ALLOCATE_ARRAY_TEMPLATE_BODY(count, p1, p2, p3, p4, p5, p6, p7)}
			template<typename Ftype, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8>                            Ftype* allocateArray(size_t count, P1& p1, P2& p2, P3& p3, P4& p4, P5& p5, P6& p6, P7& p7, P8& p8)                   {ALLOCATE_ARRAY_TEMPLATE_BODY(count, p1, p2, p3, p4, p5, p6, p7, p8)}
			template<typename Ftype, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8, typename P9>               Ftype* allocateArray(size_t count, P1& p1, P2& p2, P3& p3, P4& p4, P5& p5, P6& p6, P7& p7, P8& p8, P9& p9)           {ALLOCATE_ARRAY_TEMPLATE_BODY(count, p1, p2, p3, p4, p5, p6, p7, p8, p9)}
			template<typename Ftype, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8, typename P9, typename P10> Ftype* allocateArray(size_t count, P1& p1, P2& p2, P3& p3, P4& p4, P5& p5, P6& p6, P7& p7, P8& p8, P9& p9, P10& p10) {ALLOCATE_ARRAY_TEMPLATE_BODY(count, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10)}

			template<typename Ftype, typename P1>                                                                                                                       Ftype* allocateArray(size_t count, const P1& p1)                                                                                                                                 {ALLOCATE_ARRAY_TEMPLATE_BODY(count, p1)}
			template<typename Ftype, typename P1, typename P2>                                                                                                          Ftype* allocateArray(size_t count, const P1& p1, const P2& p2)                                                                                                                   {ALLOCATE_ARRAY_TEMPLATE_BODY(count, p1, p2)}
			template<typename Ftype, typename P1, typename P2, typename P3>                                                                                             Ftype* allocateArray(size_t count, const P1& p1, const P2& p2, const P3& p3)                                                                                                     {ALLOCATE_ARRAY_TEMPLATE_BODY(count, p1, p2, p3)}
			template<typename Ftype, typename P1, typename P2, typename P3, typename P4>                                                                                Ftype* allocateArray(size_t count, const P1& p1, const P2& p2, const P3& p3, const P4& p4)                                                                                       {ALLOCATE_ARRAY_TEMPLATE_BODY(count, p1, p2, p3, p4)}
			template<typename Ftype, typename P1, typename P2, typename P3, typename P4, typename P5>                                                                   Ftype* allocateArray(size_t count, const P1& p1, const P2& p2, const P3& p3, const P4& p4, const P5& p5)                                                                         {ALLOCATE_ARRAY_TEMPLATE_BODY(count, p1, p2, p3, p4, p5)}
			template<typename Ftype, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6>                                                      Ftype* allocateArray(size_t count, const P1& p1, const P2& p2, const P3& p3, const P4& p4, const P5& p5, const P6& p6)                                                           {ALLOCATE_ARRAY_TEMPLATE_BODY(count, p1, p2, p3, p4, p5, p6)}
			template<typename Ftype, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7>                                         Ftype* allocateArray(size_t count, const P1& p1, const P2& p2, const P3& p3, const P4& p4, const P5& p5, const P6& p6, const P7& p7)                                             {ALLOCATE_ARRAY_TEMPLATE_BODY(count, p1, p2, p3, p4, p5, p6, p7)}
			template<typename Ftype, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8>                            Ftype* allocateArray(size_t count, const P1& p1, const P2& p2, const P3& p3, const P4& p4, const P5& p5, const P6& p6, const P7& p7, const P8& p8)                               {ALLOCATE_ARRAY_TEMPLATE_BODY(count, p1, p2, p3, p4, p5, p6, p7, p8)}
			template<typename Ftype, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8, typename P9>               Ftype* allocateArray(size_t count, const P1& p1, const P2& p2, const P3& p3, const P4& p4, const P5& p5, const P6& p6, const P7& p7, const P8& p8, const P9& p9)                 {ALLOCATE_ARRAY_TEMPLATE_BODY(count, p1, p2, p3, p4, p5, p6, p7, p8, p9)}
			template<typename Ftype, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8, typename P9, typename P10> Ftype* allocateArray(size_t count, const P1& p1, const P2& p2, const P3& p3, const P4& p4, const P5& p5, const P6& p6, const P7& p7, const P8& p8, const P9& p9, const P10& p10) {ALLOCATE_ARRAY_TEMPLATE_BODY(count, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10)}
			/** @endcond */
			
			/**
			   This function resizes an array, that has previously been allocated with allocateArray().
			   @details
			   The function allocates a new array of the same type as the provided one, but with the requested element count.
			   Afterwards it copies all elements of the old array that fit into the new array into the new array by calling the copy
			   constructor of the class of the elements.
			   
			   If the new element count is lower than the old one, then the corresponding elements at the end of the old array
			   don't get copied over to the new one, but are just destructed.

			   If the new requested element count is higher than the old one, then the remaining uninitialized elements in the new array
			   get constructed by choosing the constructor that matches the provided optional arguments to reallocateArray() best (no
			   optional arguments means the default constructor gets called).

			   Finally the old array gets deallocated via deallocateArray() and the new array gets returned.

			   The returned address will most likely not match the passed one.

			   The passed address is allowed to be NULL. In that case this function behaves likes allocateArray().

			   The passed element count is allowed to be 0. In that case this function still allocates storage to store the element count
			   of 0 in, so the returned address still has to be deallocated later.

			   If the passed address has not previously been returned by a call to allocateArray() or reallocateArray() and also isn't
			   NULL or if it has already been passed to deallocateArray(), then the behavior is undefined.

			   Up to 10 optional arguments can be passed to reallocateArray() and reallocateArray() will call a constructor with the
			   matching number of parameters and matching parameter types on each element of the new array, which hasn't already been
			   copy-constructed from the corresponding element in the old array. If the class of the elements that are to be constructed,
			   doesn't provide a constructor with a matching signature or if it doesn't provide a copy constructor, if that constructor
			   or copy constructor isn't publicly accessible or if it is ambiguous, which constructor to choose, then the call to
			   reallocateArray() will trigger an error from the compiler.

			   @param p the address of the array, that is to be resized
			   @param count the new amount of elements that the array should have  */
			template<typename Ftype>                                                                                                                                    Ftype* reallocateArray(Ftype* p, size_t count)                                                                                   {REALLOCATE_ARRAY_TEMPLATE_BODY(p, count)}
			/** @cond */ 
			template<typename Ftype, typename P1>                                                                                                                       Ftype* reallocateArray(Ftype* p, size_t count, P1& p1)                                                                           {REALLOCATE_ARRAY_TEMPLATE_BODY(p, count, p1)}
			template<typename Ftype, typename P1, typename P2>                                                                                                          Ftype* reallocateArray(Ftype* p, size_t count, P1& p1, P2& p2)                                                                   {REALLOCATE_ARRAY_TEMPLATE_BODY(p, count, p1, p2)}
			template<typename Ftype, typename P1, typename P2, typename P3>                                                                                             Ftype* reallocateArray(Ftype* p, size_t count, P1& p1, P2& p2, P3& p3)                                                           {REALLOCATE_ARRAY_TEMPLATE_BODY(p, count, p1, p2, p3)}
			template<typename Ftype, typename P1, typename P2, typename P3, typename P4>                                                                                Ftype* reallocateArray(Ftype* p, size_t count, P1& p1, P2& p2, P3& p3, P4& p4)                                                   {REALLOCATE_ARRAY_TEMPLATE_BODY(p, count, p1, p2, p3, p4)}
			template<typename Ftype, typename P1, typename P2, typename P3, typename P4, typename P5>                                                                   Ftype* reallocateArray(Ftype* p, size_t count, P1& p1, P2& p2, P3& p3, P4& p4, P5& p5)                                           {REALLOCATE_ARRAY_TEMPLATE_BODY(p, count, p1, p2, p3, p4, p5)}
			template<typename Ftype, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6>                                                      Ftype* reallocateArray(Ftype* p, size_t count, P1& p1, P2& p2, P3& p3, P4& p4, P5& p5, P6& p6)                                   {REALLOCATE_ARRAY_TEMPLATE_BODY(p, count, p1, p2, p3, p4, p5, p6)}
			template<typename Ftype, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7>                                         Ftype* reallocateArray(Ftype* p, size_t count, P1& p1, P2& p2, P3& p3, P4& p4, P5& p5, P6& p6, P7& p7)                           {REALLOCATE_ARRAY_TEMPLATE_BODY(p, count, p1, p2, p3, p4, p5, p6, p7)}
			template<typename Ftype, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8>                            Ftype* reallocateArray(Ftype* p, size_t count, P1& p1, P2& p2, P3& p3, P4& p4, P5& p5, P6& p6, P7& p7, P8& p8)                   {REALLOCATE_ARRAY_TEMPLATE_BODY(p, count, p1, p2, p3, p4, p5, p6, p7, p8)}
			template<typename Ftype, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8, typename P9>               Ftype* reallocateArray(Ftype* p, size_t count, P1& p1, P2& p2, P3& p3, P4& p4, P5& p5, P6& p6, P7& p7, P8& p8, P9& p9)           {REALLOCATE_ARRAY_TEMPLATE_BODY(p, count, p1, p2, p3, p4, p5, p6, p7, p8, p9)}
			template<typename Ftype, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8, typename P9, typename P10> Ftype* reallocateArray(Ftype* p, size_t count, P1& p1, P2& p2, P3& p3, P4& p4, P5& p5, P6& p6, P7& p7, P8& p8, P9& p9, P10& p10) {REALLOCATE_ARRAY_TEMPLATE_BODY(p, count, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10)}

			template<typename Ftype, typename P1>                                                                                                                       Ftype* reallocateArray(Ftype* p, size_t count, const P1& p1)                                                                                                                                 {REALLOCATE_ARRAY_TEMPLATE_BODY(p, count, p1)}
			template<typename Ftype, typename P1, typename P2>                                                                                                          Ftype* reallocateArray(Ftype* p, size_t count, const P1& p1, const P2& p2)                                                                                                                   {REALLOCATE_ARRAY_TEMPLATE_BODY(p, count, p1, p2)}
			template<typename Ftype, typename P1, typename P2, typename P3>                                                                                             Ftype* reallocateArray(Ftype* p, size_t count, const P1& p1, const P2& p2, const P3& p3)                                                                                                     {REALLOCATE_ARRAY_TEMPLATE_BODY(p, count, p1, p2, p3)}
			template<typename Ftype, typename P1, typename P2, typename P3, typename P4>                                                                                Ftype* reallocateArray(Ftype* p, size_t count, const P1& p1, const P2& p2, const P3& p3, const P4& p4)                                                                                       {REALLOCATE_ARRAY_TEMPLATE_BODY(p, count, p1, p2, p3, p4)}
			template<typename Ftype, typename P1, typename P2, typename P3, typename P4, typename P5>                                                                   Ftype* reallocateArray(Ftype* p, size_t count, const P1& p1, const P2& p2, const P3& p3, const P4& p4, const P5& p5)                                                                         {REALLOCATE_ARRAY_TEMPLATE_BODY(p, count, p1, p2, p3, p4, p5)}
			template<typename Ftype, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6>                                                      Ftype* reallocateArray(Ftype* p, size_t count, const P1& p1, const P2& p2, const P3& p3, const P4& p4, const P5& p5, const P6& p6)                                                           {REALLOCATE_ARRAY_TEMPLATE_BODY(p, count, p1, p2, p3, p4, p5, p6)}
			template<typename Ftype, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7>                                         Ftype* reallocateArray(Ftype* p, size_t count, const P1& p1, const P2& p2, const P3& p3, const P4& p4, const P5& p5, const P6& p6, const P7& p7)                                             {REALLOCATE_ARRAY_TEMPLATE_BODY(p, count, p1, p2, p3, p4, p5, p6, p7)}
			template<typename Ftype, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8>                            Ftype* reallocateArray(Ftype* p, size_t count, const P1& p1, const P2& p2, const P3& p3, const P4& p4, const P5& p5, const P6& p6, const P7& p7, const P8& p8)                               {REALLOCATE_ARRAY_TEMPLATE_BODY(p, count, p1, p2, p3, p4, p5, p6, p7, p8)}
			template<typename Ftype, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8, typename P9>               Ftype* reallocateArray(Ftype* p, size_t count, const P1& p1, const P2& p2, const P3& p3, const P4& p4, const P5& p5, const P6& p6, const P7& p7, const P8& p8, const P9& p9)                 {REALLOCATE_ARRAY_TEMPLATE_BODY(p, count, p1, p2, p3, p4, p5, p6, p7, p8, p9)}
			template<typename Ftype, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8, typename P9, typename P10> Ftype* reallocateArray(Ftype* p, size_t count, const P1& p1, const P2& p2, const P3& p3, const P4& p4, const P5& p5, const P6& p6, const P7& p7, const P8& p8, const P9& p9, const P10& p10) {REALLOCATE_ARRAY_TEMPLATE_BODY(p, count, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10)}
			/** @endcond */

			/**
			   Call this function to destruct and deallocate an instance, that has previously been allocated and constructed by a call
			   to allocate().
			   @details
			   The passed address is allowed to be NULL. In that case the call doesn't have any effect.

			   If the passed adress has not previously been returned by a call to allocate() and also isn't NULL, then the behavior is
			   undefined.
			   @param p the address of the instance, that should be deallocated */
			template<typename Ftype>
			void deallocate(const Ftype* p)
			{
				DEALLOCATE(Ftype, p);
			}
			
			/**
			   Call this function to destruct and deallocate an array, that has previously been allocated and constructed by a call
			   to allocateArray().
			   @details
			   This function will call their destructor on all elements of the array and then deallocate the memory of the array.

			   The passed address is allowed to be NULL. In that case the call doesn't have any effect.

			   If the passed adress has not previously been returned by a call to allocateArray() or reallocateArray() and also isn't
			   NULL, then the behavior is undefined.
			   @param p the address of the array, that should be deallocated. */
			template<typename Ftype>
			void deallocateArray(const Ftype* p)
			{
				DEALLOCATE_ARRAY(Ftype, p);
			}
			/*@}*/
		}
	}
}

#ifdef _EG_WINDOWS_PLATFORM
#	pragma pop_macro("new")
#endif