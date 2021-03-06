#pragma once

#include "../common/Buffer4.h"
#include "../math/SphereBounds4.h"
#include "../math/Transform4.h"
#include "../math/Vector3.h"
#include "../visualizer/ParticleVisualizer.h"
#include "../visualizer/SolidVisualizer.h"
#include "../visualizer/WireVisualizer.h"
#include "Visualizer4.h"

namespace Forth
{
	/// <summary>
	/// Base class to handle projection from 4D to 3D
	/// </summary>
	class Projector4
	{
		friend class Model4;
		friend class Scene4;

	  protected:
		Transform4 view, viewmodel;
		unsigned long view_version = 0;

	  public:
		const Transform4& GetViewMatrix() { return view; }
		void SetViewMatrix(const Transform4& value) { view = value; ++view_version; }

		/// <summary>
		/// Dynamic projection
		/// </summary>
		virtual void Project(const Buffer4 &from, const Transform4 &transform, Visualizer4 *to) = 0;

		/// <summary>
		/// Arbitrary (4D to 3D) point projection
		/// </summary>
		virtual Vector3 Project(const Vector4 &v) const = 0;

		/// <summary>
		/// Arbitrary (4D to 3D) point projection with cull verification
		/// </summary>
		virtual Vector3 Project(const Vector4 &v, bool *culled) const = 0;

		/// <summary>
		/// For static objects, see if given object AABB can be culled out completely
		/// </summary>
		virtual bool IsCullable(const SphereBounds4 &bound) const = 0;

		/// <summary>
		/// Adapt to simplex requirement for this projection.
		/// </summary>
		virtual SimplexMode SimplexModeForVisualizing(SimplexMode mode) const = 0;

		/// <summary>
		/// Dynamic projection with default visualizer
		/// </summary>
		virtual void Project(const Buffer4 &from, const Transform4 &transform, Buffer3 &to);

	  protected:
		void *defaultVisualizers[3];

		Projector4(void);

		~Projector4(void);

	  public:
	};
} // namespace Forth
