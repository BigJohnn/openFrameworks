#pragma once
#include "ofConstants.h"
#include "ofTypes.h"
#include "ofRectangle.h"
#include "ofMatrix4x4.h"
#include "ofURLFileLoader.h"
#include "ofMesh.h"

class ofAbstractParameter;

template<typename T>
class ofImage_;

typedef ofImage_<unsigned char> ofImage;
typedef ofImage_<float> ofFloatImage;
typedef ofImage_<unsigned short> ofShortImage;

template<typename T>
class ofPixels_;

typedef ofPixels_<unsigned char> ofPixels;
typedef ofPixels_<float> ofFloatPixels;
typedef ofPixels_<unsigned short> ofShortPixels;
typedef ofPixels& ofPixelsRef;

template<typename T>
class ofColor_;

typedef ofColor_<unsigned char> ofColor;

class ofVec3f;
typedef ofVec3f ofPoint;

class ofPath;
class ofPolyline;
class ofFbo;
class of3dPrimitive;
class ofLight;
class ofMaterial;
class ofBaseMaterial;
class ofCamera;
class ofTrueTypeFont;
class ofNode;
class of3dGraphics;
class ofVbo;
class ofVboMesh;
class ofSoundBuffer;

bool ofIsVFlipped();


//----------------------------------------------------------
// ofBaseDraws
//----------------------------------------------------------

class ofBaseDraws{
public:
	/// \brief Destroy the abstract object.
	virtual ~ofBaseDraws(){}

	/// \brief Draw at a position at the native size.
	///
	/// Native size is determined by getWidth() and getHeight().
	///
	/// \param x Draw position on the x axis.
	/// \param y Draw position on the y axis.
	virtual void draw(float x, float y) const=0;

	/// \brief Draw at a position with the specified size.
	///
	/// \param x Draw position on the x axis.
	/// \param y Draw position on the y axis.
	/// \param w Draw width.
	/// \param h Draw height.
    virtual void draw(float x, float y, float w, float h) const{
        draw(x, y, getWidth(), getHeight());
    }

	/// \brief Draw at a position at the native size.
	///
	/// Native size is determined by getWidth() and getHeight().
	///
	/// \param point Draw position.
	virtual void draw(const ofPoint & point) const {
		draw(point.x, point.y);
	}

	/// \brief Draw at a position and size specified by a rectangle.
	///
	/// \param rect Draw position and size.
	virtual void draw(const ofRectangle & rect) const {
		draw(rect.x, rect.y, rect.width, rect.height);
	}

	/// \brief Draw at a position.
	///
	/// \param point Draw position.
	/// \param w Draw width.
	/// \param h Draw height.
	virtual void draw(const ofPoint & point, float w, float h) const {
		draw(point.x, point.y, w, h);
	}

	/// \brief Get the height.
	/// \returns the height.
	virtual float getHeight() const = 0;

	/// \brief Get the width.
	/// \returns the width.
	virtual float getWidth() const = 0;

	/// \brief Set the anchor point the item is drawn around as a percentage.
	///
	/// This can be useful if you want to rotate an image around a particular
	/// point.
	///
	/// \param xPct Horizontal position as a percentage (0 - 1).
	/// \param yPct Vertical position as a percentage (0 - 1).
	virtual void setAnchorPercent(float xPct, float yPct){};

	/// \brief Set the anchor point the item is drawn around in pixels.
	///
	/// This can be useful if you want to rotate an image around a particular
	/// point.
	///
	/// \param x Horizontal texture position in pixels.
	/// \param y Vertical texture position in pixels.
	virtual void setAnchorPoint(float x, float y){};

	/// \brief Reset the anchor point to (0, 0).
	virtual void resetAnchor(){};

};

/// \brief An abstract class representing an object that can be updated.
class ofBaseUpdates{
public:
	/// \brief Destroy the ofBaseUpdates.
	virtual ~ofBaseUpdates(){}

	/// \brief Update the object's state.
	virtual void update()=0;
};


class ofTexture;


/// \brief An abstract class representing an object that can have an ofTexture.
class ofBaseHasTexture{
public:
	/// \brief Destroy the ofBaseHasTexture.
	virtual ~ofBaseHasTexture(){}

	/// \returns a reference to the ofTexture.
	virtual ofTexture & getTexture()=0;

	/// \returns a const reference to the ofTexture.
	virtual const ofTexture & getTexture() const=0;

	/// \brief Enable or disable internal ofTexture use.
	/// \param bUseTex true if an ofTexture should be used.
	virtual void setUseTexture(bool bUseTex)=0;

	/// \returns true if an internal ofTexture is being used.
	virtual bool isUsingTexture() const=0;
};


/// \brief An abstract class representing an object that ofTexture planes.
class ofBaseHasTexturePlanes: public ofBaseHasTexture{
public:
	/// \brief Destroy the ofBaseHasTexturePlanes.
	virtual ~ofBaseHasTexturePlanes(){}

	/// \returns a reference to a std::vector containing the ofTexture planes.
	virtual vector<ofTexture> & getTexturePlanes()=0;

	/// \returns a const reference to a std::vector containing the ofTexture planes.
	virtual const vector<ofTexture> & getTexturePlanes() const=0;
};


/// \brief An abstract class representing an object that has pixels.
///
/// This empty class primarily exists to allow templated subclasses of different
/// types to be stored as raw or shared pointers in collections such as
/// std::vector.
///
/// Example:
/// \code{.cpp}
///
/// std::vector<ofAbstractHasPixels> pixelProviders;
///
/// ofPixels pixels;
/// ofFloatPixels floatPixels;
/// ofShortPixels shortPixels;
///
/// // ...
///
/// pixelProviders.push_back(&pixels);
/// pixelProviders.push_back(&floatPixels);
/// pixelProviders.push_back(&shortPixels);
///
/// \endcode
class ofAbstractHasPixels{
public:
	/// \brief Destroy the ofAbstractHasPixels.
	virtual ~ofAbstractHasPixels(){}
};


/// \brief A base class represeting an object that has pixels.
/// \tparam T The pixel data type.
template<typename T>
class ofBaseHasPixels_: public ofAbstractHasPixels{
public:
	/// \brief Destroy the ofAbstractHasPixels.
	virtual ~ofBaseHasPixels_<T>(){}

	/// \brief Get a reference to the underlying ofPixels.
	/// \returns a reference the underlying ofPixels.
	virtual ofPixels_<T> & getPixels()=0;

	/// \brief Get a const reference to the underlying ofPixels.
	/// \returns a const reference the underlying ofPixels.
	virtual const ofPixels_<T> & getPixels() const=0;
};

/// \brief A typedef for an unsigned char ofBaseHasPixels_.
typedef ofBaseHasPixels_<unsigned char> ofBaseHasPixels;

/// \brief A typedef for an float ofBaseHasPixels_.
typedef ofBaseHasPixels_<float> ofBaseHasFloatPixels;

/// \brief A typedef for an unsigned short ofBaseHasPixels_.
typedef ofBaseHasPixels_<unsigned short> ofBaseHasShortPixels;


/// \brief An abstract class representing an image.
///
/// This empty class primarily exists to allow templated subclasses of different
/// types to be stored as raw or shared pointers in collections such as
/// std::vector.
///
/// Example:
/// \code{.cpp}
///
/// std::vector<ofAbstractImage*> imageProviders;
///
/// ofImage image;
/// ofFloatImage floatImage;
/// ofShortImage shortImage;
///
/// // ...
///
/// imageProviders.push_back(&image);
/// imageProviders.push_back(&floatImage);
/// imageProviders.push_back(&shortImage);
///
/// \endcode
class ofAbstractImage: public ofBaseDraws, public ofBaseHasTexture{
public:
	/// \brief Destroy the ofAbstractImage.
	virtual ~ofAbstractImage(){}
};

/// \brief A base class represeting an image.
/// \tparam T The pixel data type.
template<typename T>
class ofBaseImage_: public ofAbstractImage, virtual public ofBaseHasPixels_<T>{
public:
	/// \brief Destroy the ofBaseImage_.
	virtual ~ofBaseImage_<T>(){};
};


/// \brief A typedef for an unsigned char ofBaseImage_.
typedef ofBaseImage_<unsigned char> ofBaseImage;

/// \brief A typedef for an float ofBaseImage_.
typedef ofBaseImage_<float> ofBaseFloatImage;

/// \brief A typedef for an unsigned short ofBaseImage_.
typedef ofBaseImage_<unsigned short> ofBaseShortImage;



/// \brief A base class representing a sound input stream.
class ofBaseSoundInput{
	public:
		/// \brief Destroy the ofBaseSoundInput.
		virtual ~ofBaseSoundInput() {};

		/// \brief Receive an audio buffer.
	    /// \param buffer An audio buffer.
		virtual void audioIn( ofSoundBuffer& buffer );

		/// \deprecated This legacy method is deprecated and will be removed.
		/// Use void audioIn(ofSoundBuffer& buffer) instead.
		virtual void audioIn( float * input, int bufferSize, int nChannels, int deviceID, long unsigned long tickCount );

		/// \deprecated This legacy method is deprecated and will be removed.
		/// Use void audioIn(ofSoundBuffer& buffer) instead.
		virtual void audioIn( float * input, int bufferSize, int nChannels );

		/// \deprecated This legacy method is deprecated and will be removed.
		/// Use void audioIn(ofSoundBuffer& buffer) instead.
		virtual void audioReceived( float * input, int bufferSize, int nChannels ){}
};


/// \brief A base class representing a sound output stream.
class ofBaseSoundOutput{
	public:
		/// \brief Destroy the ofBaseSoundOutput.
		virtual ~ofBaseSoundOutput() {};
	
		/// \brief Output an audio buffer.
		/// \param buffer An audio buffer.
		virtual void audioOut( ofSoundBuffer& buffer );

		/// \deprecated This legacy method is deprecated and will be removed.
		/// Use void audioOut(ofSoundBuffer& buffer) instead.
		virtual void audioOut( float * output, int bufferSize, int nChannels, int deviceID, long unsigned long tickCount  );

		/// \deprecated This legacy method is deprecated and will be removed.
		/// Use void audioOut(ofSoundBuffer& buffer) instead.
		virtual void audioOut( float * output, int bufferSize, int nChannels );

		/// \deprecated This legacy method is deprecated and will be removed.
		/// Use void audioOut(ofSoundBuffer& buffer) instead.
		virtual void audioRequested( float * output, int bufferSize, int nChannels ){}
};


/// \brief A base class representing a video source.
class ofBaseVideo: virtual public ofBaseHasPixels, public ofBaseUpdates{
public:
	/// \brief Destroy the ofBaseVideo.
	virtual ~ofBaseVideo(){}

	/// \returns true if the pixel data was updated since the last call to update().
	virtual bool isFrameNew() const =0;

	/// \brief Close the video source.
	virtual void close()=0;

	/// \brief Determine if the video source is initialized.
	///
	/// Video sources such as cameras are often initialized with a
	/// setup() method.  Video sources such as movie players are often
	/// initialized with a load() method.
	///
	/// \returns true if the video source is initialized.
	virtual bool isInitialized() const=0;

	/// \brief Set the requested ofPixelFormat.
	/// \param pixelFormat the requested ofPixelFormat.
	/// \returns true if the format was successfully changed.
	virtual bool setPixelFormat(ofPixelFormat pixelFormat) = 0;

	/// \returns the current ofPixelFormat.
	virtual ofPixelFormat getPixelFormat() const = 0;
};


/// \brief A base class representing a drawable video source.
class ofBaseVideoDraws:
	virtual public ofBaseVideo,
	public ofBaseDraws,
	public ofBaseHasTexturePlanes,
	virtual public ofBaseHasPixels{
public:
	/// \brief Destroy the ofBaseVideoDraws.
	virtual ~ofBaseVideoDraws(){}
};

/// \brief A base class representing a video device such as a camera.
class ofBaseVideoGrabber: virtual public ofBaseVideo{

	public :
	/// \brief Destroy the ofBaseVideoGrabber
	virtual ~ofBaseVideoGrabber();

	//needs implementing
	/// \brief Get a list of available video grabber devices.
	/// \returns a std::vector of ofVideoDevice objects.
	virtual vector<ofVideoDevice>	listDevices() const = 0;

	/// \brief Set up the grabber with the requested width and height.
	///
	/// Some video grabbers may take the requested width and height as
	/// a hint and choose the closest dimensions to those requested.
	/// Users can check the actual width and height by calling getWidth() and
	/// getHeight() respectively after a successful setup.
	///
	/// \param w the requested width.
	/// \param h the requested height.
	/// \returns true if the video grabber was set up successfully.
	virtual bool setup(int w, int h) = 0;

	/// \brief Get the video grabber's height.
	/// \returns the video grabber's height.
	virtual float getHeight() const = 0;

	/// \brief Get the video grabber's width.
	/// \returns the video grabber's width.
	virtual float getWidth() const = 0;

	/// \brief Get the video grabber's internal ofTexture pointer if available.
	///
	/// \note Subclasses should implement this method only if internal API can
	/// upload video grabber pixels directly to an ofTexture.
	///
	/// \returns the internal ofTexture pointer or nullptr if not available.
	virtual ofTexture * getTexturePtr(){ return nullptr; }

	/// \brief Set the video grabber's hardware verbosity level.
	/// \param bTalkToMe true if verbose grabber logging feedback is required.
	virtual void setVerbose(bool bTalkToMe);

	/// \brief Set the video grabber's device ID.
	///
	/// In most cases, a user can choose a specific grabber source by ID.  This
	/// device ID information should be available to the user via the
	/// listDevices() method.
	///
	/// \param deviceID The device ID provided by listDevices().
	virtual void setDeviceID(int deviceID);

	/// \brief Set the video grabber's desired frame rate.
	///
	/// Many video grabbers support user-specified frame rates.  This frame rate
	/// should be considered a hint for the video grabber and is not guaranteed.
	///
	/// \param framerate the desired frame rate.
	virtual void setDesiredFrameRate(int framerate);

	/// \brief Request a native GUI for video grabber settings.
	/// \note This feature may not be implemented by all video grabbers.
	virtual void videoSettings();

};


/// \brief A base class representing a video player.
class ofBaseVideoPlayer: virtual public ofBaseVideo{

public:
	/// \brief Destroys the ofBaseVideoPlayer.
	virtual ~ofBaseVideoPlayer();

	/// \brief Load a video resource by name.
	///
	/// The list of supported video types and sources (e.g. rtsp:// sources) is
	/// implementation dependent.
	///
	/// \param name The name of the video resource to load.
	/// \returns True if the video was loaded successfully.
	/// \sa loadAsync()
	virtual bool				load(string name) = 0;
	/// \brief Asynchronously load a video resource by name.
	///
	/// The list of supported video types and sources (e.g. rtsp:// sources) is
	/// implementation dependent.
	///
	/// When this method is used to load a video resouce, users can determine
	/// when the video is loaded by calling isLoaded().
	///
	/// \param name The name of the video resource to load.
	/// \sa isLoaded()
	virtual void				loadAsync(string name);
	
	/// \brief Play the video from the current playhead position.
	/// \sa getPosition()
	/// \sa setPostion()
	virtual void				play() = 0;
	/// \brief Pause and reset the playhead position to the first frame.
	virtual void				stop() = 0;
	/// \brief Get a pointer to the video texture used internally if it exists.
	///
	/// If the video player implementation supports direct-to-texture rendering,
	/// this method will return a pointer to the internal texture. If
	/// direct-to-texture rendering is not supported, nullptr is returned.
	///
	/// \returns A valid pointer to the internal texture, otherwise a nullptr.
	virtual ofTexture *			getTexturePtr(){return nullptr;};

	/// \brief Get the width in pixels of the loaded video.
	/// \returns The width in pixels of the loaded video or 0 if none is loaded.
	virtual float 				getWidth() const = 0;
	/// \brief Get the height in pixels of the loaded video.
	/// \returns The height in pixels of the loaded video or 0 if none is loaded.
	virtual float 				getHeight() const = 0;

	/// \brief Returns true if the video is paused.
	/// \returns True if the video is paused.
	virtual bool				isPaused() const = 0;
	/// \brief Returns true if a video is loaded.
	///
	/// This is helpful when loading a video with loadAsync(). This is also an
	/// alias of isInitialized().
	///
	/// \sa loadAsync()
	/// \returns True if a video is loaded.
	virtual bool				isLoaded() const = 0;
	/// \brief Returns true if the loaded video is playing.
	/// \returns True if the loaded video is playing.
	virtual bool				isPlaying() const = 0;
	/// \brief Returns true if a video is loaded.
	///
	/// This is helpful when loading a video with loadAsync(). This is also
	/// an alias of isLoaded().
	///
	/// \sa loadAsync()
	/// \returns True if a video is loaded.
	virtual bool				isInitialized() const{ return isLoaded(); }

	/// \brief Get the current playhead position of the loaded video.
	///
	/// This value is a normalized floating point value between 0.0 and 1.0 that
	/// represents the position of the playhead. 0.0 maps to the first frame of
	/// the loaded video and 1.0 maps to the last frame of the loaded video.
	///
	/// \returns A value between 0.0 and 1.0 representing playhead position.
	virtual float 				getPosition() const;
	/// \brief Get the playback speed of the video player.
	///
	/// When the loop state is OF_LOOP_NONE or OF_LOOP_NORMAL, positive speed
	/// will scale a forward playback rate while a negative speed will scale a
	/// a backward playback rate. When the loop state is OF_LOOP_PALINDROME,
	/// the direction of playback will change each loop, but the playback rate
	/// will still be scaled by the absolute value of the speed.
	///
	/// \returns The playback speed of the video player.
	virtual float 				getSpeed() const;
	/// \brief Get the duration of the loaded video in seconds.
	/// \returns The duration of the loaded video in seconds.
	virtual float 				getDuration() const;
	/// \brief Returns true if the loaded video has finished playing.
	/// \returns True if the loaded video has finished playing.
	virtual bool				getIsMovieDone() const;

	/// \brief Set the paused state of the video.
	/// \param bPause True to pause the video, false to play.
	virtual void 				setPaused(bool bPause);
	/// \brief Set the position of the playhead.
	///
	/// This value is a normalized floating point value between 0.0 and 1.0 that
	/// represents the position of the playhead. 0.0 maps to the first frame of
	/// the loaded video and 1.0 maps to the last frame of the loaded video.
	///
	/// \param pct A value between 0.0 and 1.0 representing playhead position.
	virtual void 				setPosition(float pct);
	/// \brief Set the volume of the video player.
	///
	/// This value is a normalized floating point value between 0.0 and 1.0 that
	/// represents the video player volume. 0.0 maps to silence and 1.0 maps to
	/// maximum volume.
	///
	/// \param volume A value between 0.0 and 1.0 representing volume.
	virtual void 				setVolume(float volume);
	/// \brief Set the video loop state.
	/// \param state The loop state of the video.
	/// \sa ::ofLoopType
	virtual void 				setLoopState(ofLoopType state);
	/// \brief Set the video playback speed.
	///
	/// When the loop state is OF_LOOP_NONE or OF_LOOP_NORMAL, positive speed
	/// will scale a forward playback rate while a negative speed will scale a
	/// a backward playback rate. When the loop state is OF_LOOP_PALINDROME,
	/// the direction of playback will change each loop, but the playback rate
	/// will still be scaled by the absolute value of the speed.
	///
	/// To play a video forward at normal speed, set the loop state to
	/// OF_LOOP_NONE or OF_LOOP_NORMAL and a speed of 1.0. To double the
	/// playback rate, set the speed to 2.0. To play a video backward, set the
	/// speed to a negative number. A speed 0.25 will play the video at 1/4 the
	/// the normal rate and a rate of 0.0 will effectively stop playback.
	///
	/// \param speed The desired playback speed of the video.
	virtual void   				setSpeed(float speed);
	/// \brief Set the current frame by frame number.
	///
	/// Similar to setPosition(), but accepts a frame number instead of
	/// a normalized floating point value. Frame count begins with the first
	/// frame as 0 and the last frame as getTotalNumFrames() - 1.
	///
	/// \param frame The frame number to set the new playhead to.
	virtual void				setFrame(int frame);

	/// \brief Get the current playhead position as a frame number.
	/// \returns The current playhead position as a frame number.
	virtual int					getCurrentFrame() const;
	/// \brief Get the total number of frames in the currently loaded video.
	/// \returns The total number of frames in the currently loaded video.
	virtual int					getTotalNumFrames() const;
	/// \brief Get the current loop state of the video.
	/// \sa ::ofLoopType
	virtual ofLoopType			getLoopState() const;

	/// \brief Set the playhead position to the first frame.
	///
	/// This is functionally equivalent to setFrame(0) or setPosition(0.0).
	virtual void				firstFrame();
	/// \brief Advance the playhead forward one frame.
	///
	/// This allows the user to advance through the video manually one frame at
	/// a time without calling play().
	virtual void				nextFrame();
	/// \brief Advance the playhead backward one frame.
	///
	/// This allows the user to advance backward through the video manually one
	/// frame at a time without calling play().
	virtual void				previousFrame();
};

//----------------------------------------------------------
// base renderers
//----------------------------------------------------------
class of3dPrimitive;

class ofBaseRenderer{
public:
	virtual ~ofBaseRenderer(){}

	/// \brief Get the string representation of the renderer type.
	///
	/// For example, this method may return "GL" or "ProgrammableGL", or another
	/// type depending on the renderer you are using.
	///
	/// \returns The string representation of the renderer type.
	virtual const string & getType()=0;

	/// \brief Starts using this renderer.
	virtual void startRender() = 0;
	/// \brief Finishes using this renderer.
	virtual void finishRender() = 0;

	/// \brief Draw the ofPolyline \p poly to this renderer.
	/// \param poly The ofPolyline to draw to this renderer.
	virtual void draw(const ofPolyline & poly) const=0;
	/// \brief Draw the ofPath \p shape to this renderer.
	/// \param shape The ofPath to draw to this renderer.
	virtual void draw(const ofPath & shape) const=0;
	/// \brief Draw the ofPath \p shape to this renderer.
	/// \param shape The ofPath to draw to this renderer.
	/// \param x The x coordinate to use when drawing \p shape.
	/// \param y The y coordinate to use when drawing \p shape.
	virtual void draw(const ofPath & shape, float x, float y) const{
		const_cast<ofBaseRenderer*>(this)->pushMatrix();
		const_cast<ofBaseRenderer*>(this)->translate(x,y);
		draw(shape);
		const_cast<ofBaseRenderer*>(this)->popMatrix();
	}
	/// \brief Draw the \p mesh to this renderer using the \p renderType.
	///
	/// \p renderType defines how the \p mesh will be rendered and may be:
	/// 	OF_MESH_POINTS,
	///		OF_MESH_WIREFRAME,
	///		OF_MESH_FILL
	///
	/// \param mesh The mesh to draw to this renderer.
	/// \param ofPolyRenderMode The render mode to use when drawing \p mesh to
	/// this renderer.
	/// \sa ofPolyRenderMode
	virtual void draw(const ofMesh & mesh, ofPolyRenderMode renderType) const{
		draw(mesh,renderType,mesh.usingColors(),mesh.usingTextures(),mesh.usingNormals());
	}
	/// \brief Draw the \p vertexData to this renderer.
	/// \param vertexData The mesh to draw to this renderer.
	/// \param useColors True to use per-vertex coloring when drawing the
	/// \p vertexData.
	/// \param useTextures True to use texture coordinates when drawing the \p
	/// vertexData.
	/// \param useNormals True to use normals when drawing the \p vertexData.
	/// \sa ofPolyRenderMode
	virtual void draw(const ofMesh & vertexData, ofPolyRenderMode renderType, bool useColors, bool useTextures, bool useNormals) const=0;
	/// \brief Draw the \p model to this renderer using the \p renderType.
	///
	/// \p renderType defines how the \p model will be rendered and may be:
	/// 	OF_MESH_POINTS,
	///		OF_MESH_WIREFRAME,
	///		OF_MESH_FILL
	///
	/// \param model The mesh to draw to this renderer.
	/// \param ofPolyRenderMode The render mode to use when drawing the \p model
	/// to this renderer.
	/// \sa ofPolyRenderMode
	virtual void draw(const of3dPrimitive& model, ofPolyRenderMode renderType) const=0;
	/// \brief Draw the \model to this renderer.
	virtual void draw(const ofNode& model) const=0;
	/// \brief Draw the \p image to this renderer.
	/// \param image The image to draw to this renderer.
	/// \param x The x coordinate to use when drawing to this renderer.
	/// \param y The y coordinate to use when drawing to this renderer.
	/// \param z The z coordinate to use when drawing to this renderer.
	/// \param w The width to use when drawing the image to this renderer.
	/// \param h The height to use when drawing the image to this renderer.
	/// \param sx The subsection x axis offset within the image texture.
	/// \param sy The subsection y axis offset within the image texture.
	/// \param sw The subsection width offset within the image texture.
	/// \param sh The subsection height offset within the image texture.
	virtual void draw(const ofImage & image, float x, float y, float z, float w, float h, float sx, float sy, float sw, float sh) const=0;
	/// \brief Draw the \p image to this renderer.
	/// \param image The image to draw to this renderer.
	/// \param x The x coordinate to use when drawing to this renderer.
	/// \param y The y coordinate to use when drawing to this renderer.
	/// \param z The z coordinate to use when drawing to this renderer.
	/// \param w The width to use when drawing the image to this renderer.
	/// \param h The height to use when drawing the image to this renderer.
	/// \param sx The subsection x axis offset within the image texture.
	/// \param sy The subsection y axis offset within the image texture.
	/// \param sw The subsection width offset within the image texture.
	/// \param sh The subsection height offset within the image texture.
	virtual void draw(const ofFloatImage & image, float x, float y, float z, float w, float h, float sx, float sy, float sw, float sh) const=0;
	/// \brief Draw the \p image to this renderer.
	/// \param image The image to draw to this renderer.
	/// \param x The x coordinate to use when drawing to this renderer.
	/// \param y The y coordinate to use when drawing to this renderer.
	/// \param z The z coordinate to use when drawing to this renderer.
	/// \param w The width to use when drawing the image to this renderer.
	/// \param h The height to use when drawing the image to this renderer.
	/// \param sx The subsection x axis offset within the image texture.
	/// \param sy The subsection y axis offset within the image texture.
	/// \param sw The subsection width offset within the image texture.
	/// \param sh The subsection height offset within the image texture.
	virtual void draw(const ofShortImage & image, float x, float y, float z, float w, float h, float sx, float sy, float sw, float sh) const=0;
	/// \brief Draw the \p video to this renderer.
	/// \param video The video to draw to this renderer.
	/// \param x The x coordinate to use when drawing to this renderer.
	/// \param y The y coordinate to use when drawing to this renderer.
	/// \param w The width to use when drawing the video to this renderer.
	/// \param h The height to use when drawing the video to this renderer.
	virtual void draw(const ofBaseVideoDraws & video, float x, float y, float w, float h) const=0;

	//--------------------------------------------
	// transformations
	/// \brief Push the current viewport into the renderer's viewport stack.
	/// \sa viewport()
	virtual void pushView()=0;
	/// \brief Pop the current viewport from the renderer's view stack.
	/// \sa viewport()
	virtual void popView()=0;

	// setup matrices and viewport (upto you to push and pop view before and after)
	// if width or height are 0, assume windows dimensions (ofGetWidth(), ofGetHeight())
	// if nearDist or farDist are 0 assume defaults (calculated based on width / height)
	/// \brief Set this renderer's viewport using a rectangle.
	virtual void viewport(ofRectangle viewport)=0;
	/// \brief Set this renderer's viewport using x, y, width, and height.
	virtual void viewport(float x = 0, float y = 0, float width = -1, float height = -1, bool vflip=true)=0;
	/// \brief Set the perspective matrix to use a perspective matrix.
	/// distance.
	/// \params width The width of the desired perspective matrix. Defaults to
	/// -1 and is ignored.
	/// \params height The height of the desired perspective matrix. Defaults to
	/// -1 and is ignored.
	/// \params fov The field of view to use with the perspective matrix.
	/// Defaults to 60.
	/// \params nearDist The near clipping distance to use with the perspective
	/// matrix. Setting this value to 0 uses the defualt near distance. Defaults
	/// to 0.
	/// \params nearDist The far clipping distance to use with the perspective
	/// matrix. Setting this value to 0 uses the defualt near distance. Defaults
	/// to 0.
	virtual void setupScreenPerspective(float width = -1, float height = -1, float fov = 60, float nearDist = 0, float farDist = 0)=0;
	/// \brief Set the renderer to use an orthographic matrix.
	/// \params width The width of the desired perspective matrix. Defaults to
	/// -1 and is ignored.
	/// \params height The height of the desired perspective matrix. Defaults to
	/// -1 and is ignored.
	/// \params nearDist The near clipping distance to use with the perspective
	/// matrix. Setting this value to 0 uses the defualt near distance. Defaults
	/// to 0.
	/// \params nearDist The far clipping distance to use with the perspective
	/// matrix. Setting this value to 0 uses the defualt near distance. Defaults
	/// to 0.
	virtual void setupScreenOrtho(float width = -1, float height = -1, float nearDist = -1, float farDist = 1)=0;
	/// \brief set this renderer's orientation.
	///
	/// Possible orientation values include:
	/// 	OF_ORIENTATION_DEFAULT
	///		OF_ORIENTATION_180
    ///		OF_ORIENTATION_90_LEFT
	///		OF_ORIENTATION_90_RIGHT
    ///		OF_ORIENTATION_UNKNOWN
	///
	/// \params orientation The orientation to use with this renderer.
	/// \params vFlip True if the orientation should be vertically flipped.
	/// \sa ofOrientation
	virtual void setOrientation(ofOrientation orientation, bool vFlip)=0;
	/// \brief Get this renderer's current viewport.
	///
	/// Unlike getNativeViewport(), this method gets this renderer's current
	/// viewport with orientation and vertical flipping applied.
	///
	/// \returns Returns this renderer's viewport as a rectangle.
	/// \sa getNativeViewport()
	virtual ofRectangle getCurrentViewport() const=0;
	
	/// \brief Get this renderer's current native viewport.
	///
	/// Unlike getViewport(), this method gets this renderer's current viewport
	/// without orientation and vertical flipping applied.
	///
	/// \returns Returns this renderer's native viewport as a rectangle.
	/// \sa getViewport()
	virtual ofRectangle getNativeViewport() const=0;
	/// \brief get the renderer's current viewport width.
	/// \returns the renderer's current viewport width.
	virtual int getViewportWidth() const=0;
	/// \brief get the renderer's current viewport width.
	/// \returns the renderer's current viewport width.
	virtual int getViewportHeight() const=0;
	/// \brief Returns true if the renderer's current viewport is vertically
	/// flipped.
	/// \returns True if the renderer's current viewport is vertically flipped.
	virtual bool isVFlipped() const=0;

	/// \brief Set the coordinate handidness of this renderer.
	///
	/// Possible handednesses include OF_LEFT_HANDED and OF_RIGHT_HANDED.
	/// In a left handed coordinate system positive x, y and z axes point right,
	/// up and forward, respectively and positive rotation is clockwise about
	/// the axis of rotation. In a right handed coordinate system the positive x
	/// and y axes point right and up, and the negative z axis points forward
	/// and positive rotation is counterclockwise about the axis of rotation.
	///
	/// \param handedness The handedness to request this renderer to use.
	/// \sa http://seanmiddleditch.com/matrices-handedness-pre-and-post-multiplication-row-vs-column-major-and-notations/
	/// \sa https://www.evl.uic.edu/ralph/508S98/coordinates.html
	virtual void setCoordHandedness(ofHandednessType handedness)=0;
	
	/// \brief Get the coordinate handidness of this renderer.
	///
	/// Possible handednesses include OF_LEFT_HANDED and OF_RIGHT_HANDED.
	/// In a left handed coordinate system positive x, y and z axes point right,
	/// up and forward, respectively and positive rotation is clockwise about
	/// the axis of rotation. In a right handed coordinate system the positive x
	/// and y axes point right and up, and the negative z axis points forward
	/// and positive rotation is counterclockwise about the axis of rotation.
	///
	/// \returns The handedness this renderer is using.
	/// \sa http://seanmiddleditch.com/matrices-handedness-pre-and-post-multiplication-row-vs-column-major-and-notations/
	/// \sa https://www.evl.uic.edu/ralph/508S98/coordinates.html
	virtual ofHandednessType getCoordHandedness() const=0;

	//our openGL wrappers
	
	/// \brief Pushes this renderer's matrix into its matrix stack.
	///
	/// pushMatrix() saves the renderer's current coordinate system matrix
	/// allowing new transformations and scales to effect only the new matrix
	/// created by this method. Should be paired with a call to popMatrix().
	virtual void pushMatrix()=0;
	/// \brief Pops this renderer's matrix from its matrix stack.
	///
	/// popMatrix() restores the renderer's current coordinate system matrix
	/// to its last saved state set with pushMatrix().
	virtual void popMatrix()=0;
	/// \brief Get this renderer's current matrix for particular a matrix mode.
	///
	/// Possible matrix modes include:
	///		OF_MATRIX_MODELVIEW
	///		OF_MATRIX_PROJECTION
	///		OF_MATRIX_TEXTURE
	///
	/// \params matrixMode_ The matrix mode to get the current matrix of.
	/// \returns The current matrix specified by \p matrixMode_
	virtual ofMatrix4x4 getCurrentMatrix(ofMatrixMode matrixMode_) const=0;
	/// \brief Get this renderer's current orientation matrix.
	/// \returns This renderer's current orientation matrix.
	virtual ofMatrix4x4 getCurrentOrientationMatrix() const=0;
	/// \brief Translate this renderer's current matrix by x, y, and z.
	/// \params x The x coordinate to translate this renderer's current matrix
	/// by.
	/// \params y The y coordinate to translate this renderer's current matrix
	/// by.
	/// \params z The z coordinate to translate this renderer's current matrix
	/// by.
	virtual void translate(float x, float y, float z = 0)=0;
	/// \brief Translate this renderer's current matrix by a point.
	/// \params p The 3D point to translate this renderer's current matrix by.
	virtual void translate(const ofPoint & p)=0;
	/// \brief Scale this renderer's current matrix by xAmnt, yAmnt, and zAmnt.
	/// \params xAmnt The amount to scale this renderer's current matrix's x
	/// axis by.
	/// \params yAmnt The amount to scale this renderer's current matrix's x
	/// axis by.
	/// \params zAmnt The amount to scale this renderer's current matrix's x
	/// axis by. Defaults to 1.
	virtual void scale(float xAmnt, float yAmnt, float zAmnt = 1)=0;
	/// \brief Rotate this renderer's current matrix by \p degrees about a euler.
	/// \params degrees Degrees to rotate about vecX, vecY, and vecZ.
	/// \params vecX The x axis to rotate about.
	/// \params vecY The y axis to rotate about.
	/// \params vecZ The z axis to rotate about.
	virtual void rotate(float degrees, float vecX, float vecY, float vecZ)=0;
	/// \brief Rotate this renderer's current matrix by \p degrees about the x
	/// axis.
	/// \params degrees Degrees to rotate about the x axis.
	virtual void rotateX(float degrees)=0;
	/// \brief Rotate this renderer's current matrix by \p degrees about the y
	/// axis.
	/// \params degrees Degrees to rotate about the y axis.
	virtual void rotateY(float degrees)=0;
	/// \brief Rotate this renderer's current matrix by \p degrees about the z
	/// axis.
	/// \params degrees Degrees to rotate about the z axis.
	virtual void rotateZ(float degrees)=0;
	/// \brief Rotate this renderer's current matrix by \p degrees about the z
	/// axis.
	///
	/// This method is an alias of rotateZ().
	///
	/// \params degrees Degrees to rotate about the z axis.
	/// \sa rotateZ()
	virtual void rotate(float degrees)=0;
	/// \brief Sets this renderer's current matrix mode.
	///
	/// The possible matrix modes include:
	///		OF_MATRIX_MODELVIEW
	///		OF_MATRIX_PROJECTION
	///		OF_MATRIX_TEXTURE
	///
	/// \param mode The matrix mode this renderer's matrix should use.
	virtual void matrixMode(ofMatrixMode mode)=0;
	
	/// \param Load this renderer's identity matrix.
	///
	/// This identity matrix is an ofMatrix4x4 matrix with 1s on the main
	/// diagonal and 0s elsewhere.
	/// [
	///		[1, 0, 0, 0],
	///		[0, 1, 0, 0],
	///		[0, 0, 1, 0],
	///		[0, 0, 0, 1]
	///	]
	virtual void loadIdentityMatrix (void)=0;
	/// \brief Load m as this renderer's current matrix.
	/// \param m The matrix to load into this renderer.
	virtual void loadMatrix (const ofMatrix4x4 & m)=0;
	/// \brief Load m as this renderer's current matrix.
	///
	/// m can be passed to loadMatrix() in this way with ofMatrix4x4::getPtr().
	///
	/// \param m Float pointer to an ofMatrix4x4.
	virtual void loadMatrix (const float *m)=0;
	/// \brief Multiply this renderer's current matrix by \p m.
	/// \param m The matrix to multiply this renderer's current matrix by.
	virtual void multMatrix (const ofMatrix4x4 & m)=0;
	/// \brief Multiply this renderer's current matrix by \p m.
	///
	/// m can be passed to loadMatrix() in this way with ofMatrix4x4::getPtr().
	///
	/// \param m Float pointer to an ofMatrix4x4 to multiply this renderer's
	/// current matrix by.
	virtual void multMatrix (const float *m)=0;
	/// \brief Load \p m into this renderer's matrix stack as view matrix.
	/// \param The view matrix to load into this renderer's matrix stack.
	virtual void loadViewMatrix(const ofMatrix4x4 & m)=0;
	/// \brief Multiply this renderer's view matrix by \p m.
	/// \param The matrix to multiply this renderer's view matrix by.
	virtual void multViewMatrix(const ofMatrix4x4 & m)=0;
	/// \brief Get this renderer's current view matrix.
	/// \returns This renderer's current view matrix.
	virtual ofMatrix4x4 getCurrentViewMatrix() const=0;
	/// \brief Get this renderer's current normal matrix.
	/// \returns This renderer's current normal matrix.
	virtual ofMatrix4x4 getCurrentNormalMatrix() const=0;
	
	// bind common objects that need perspective settings
	/// \brief Bind \p camera's matrices to this renderer's matrix stack.
	///
	/// Bind's the \p camera's modelview and projection matrices to this
	/// renderer's matrix stack using \p viewport. Should be followed with a
	/// call to
	///
	/// \param camera The camera to bind to this renderer.
	/// \param viewport The viewport to use when binding \p camera to this
	/// renderer.
	virtual void bind(const ofCamera & camera, const ofRectangle & viewport)=0;
	/// \brief Unbind the camera from this renderer.
	/// \params The camera to unbind from this renderer.
	virtual void unbind(const ofCamera & camera)=0;

	// screen coordinate things / default gl values
	/// \brief setup the graphic defaults.
	virtual void setupGraphicDefaults()=0;
	/// \brief setup the screen.
	virtual void setupScreen()=0;

	// drawing modes
	/// \brief Set this renderer's rect mode.
	///
	/// Possible rect modes include OF_RECTMODE_CORNER and OF_RECTMODE_CENTER.
	///
	/// \param mode The rect mode to request this renderer to use.
	/// \sa ofRectMode
	virtual void setRectMode(ofRectMode mode)=0;
	/// \brief Get this renderer's current rect mode.
	///
	/// Possible rect modes include OF_RECTMODE_CORNER and OF_RECTMODE_CENTER.
	///
	/// \returns The renderer's current rect mode.
	/// \sa ofRectMode
	virtual ofRectMode getRectMode()=0;
	/// \brief set this renderer's fill flag.
	///
	/// Possible fill flags include OF_OUTLINE and OF_FILLED.
	///
	/// \param fill The fill flag to request this renderer to use.
	/// \sa ofFillFlag
	virtual void setFillMode(ofFillFlag fill)=0;
	/// \brief Get this renderer's current fill flag.
	///
	/// Possible fill flags include OF_OUTLINE and OF_FILLED.
	///
	/// \returns The fill flag this render is currently using.
	/// \sa ofFillFlag
	virtual ofFillFlag getFillMode()=0;
	/// \brief Set the line width this renderer should use when drawing lines.
	/// \param lineWidth The line width to request this renderer to use.
	virtual void setLineWidth(float lineWidth)=0;
	/// \brief Enable/disable depth testing with this renderer.
	///
	/// When depth testing is enabled the order shapes are drawn to the
	/// renderer is dependent on their distance from the camera rather than the
	/// order their drawing methods were called. This should be enabled when
	/// expecting normal behavior when drawing 3D scenes.
	///
	/// \param depthTest True to enable depth testing.
	virtual void setDepthTest(bool depthTest)=0;
	/// \brief Set this renderer's current blend mode.
	///
	/// Possible blend modes include:
	///		OF_BLENDMODE_DISABLED
	///		OF_BLENDMODE_ALPHA
	///		OF_BLENDMODE_ADD
	///		OF_BLENDMODE_SUBTRACT
	///		OF_BLENDMODE_MULTIPLY
	///		OF_BLENDMODE_SCREEN
	///
	/// \params blendMode The blend mode to request this renderer to use.
	/// \sa ofBlendMode
	/// \sa https://helpx.adobe.com/photoshop/using/blending-modes.html
	virtual void setBlendMode(ofBlendMode blendMode)=0;
	/// \brief Enable/disable line smoothing for this renderer if its supported.
	/// \param True to enable line smoothing for this renderer if its supported.
	virtual void setLineSmoothing(bool smooth)=0;
	/// \brief Set the resolution to use when drawing ellipses with this
	/// renderer.
	/// \param res The number of points to use when drawing circles and ellipses
	/// with this renderer.
	virtual void setCircleResolution(int res)=0;
	/// \brief Enable this renderer to use anti aliasing if it is supported.
	virtual void enableAntiAliasing()=0;
	/// \brief Disable this renderer from using anti aliasing.
	virtual void disableAntiAliasing()=0;

	/// \brief Set the global color this renderer will use when drawing.
	///
	/// The renderer will continue using a color set by setColor() until another
	/// call to setColor() changes the drawing color.
	///
	/// \param r The red value between 0 and 255 to use when drawing.
	/// \param g The green value between 0 and 255 to use when drawing.
	/// \param b The blue value between 0 and 255 to use when drawing.
	virtual void setColor(int r, int g, int b)=0;
	/// \brief Set the global color this renderer will use when drawing.
	///
	/// The renderer will continue using a color set by setColor() until another
	/// call to setColor() changes the drawing color.
	///
	/// \param r The red value between 0 and 255 to use when drawing.
	/// \param g The green value between 0 and 255 to use when drawing.
	/// \param b The blue value between 0 and 255 to use when drawing.
	/// \param a The alpha value between 0 and 255 to use when drawing.
	virtual void setColor(int r, int g, int b, int a)=0;
	/// \brief Set the global color this renderer will use when drawing.
	///
	/// The renderer will continue using a color set by setColor() until another
	/// call to setColor() changes the drawing color.
	///
	/// \param color The color to use when drawing.
	virtual void setColor(const ofColor & color)=0;
	/// \brief Set the global color this renderer will use when drawing.
	///
	/// The renderer will continue using a color set by setColor() until another
	/// call to setColor() changes the drawing color.
	///
	/// \param color The color to use when drawing.
	/// \param _a The alpha value between 0 and 255 to use when drawing.
	virtual void setColor(const ofColor & color, int _a)=0;
	/// \brief Set the global color this renderer will use when drawing.
	///
	/// The renderer will continue using a color set by setColor() until another
	/// call to setColor() changes the drawing color.
	///
	/// \param gray The grayscale value to use when drawing.
	virtual void setColor(int gray)=0;
	/// \brief Set the global color this renderer will use when drawing.
	///
	/// The renderer will continue using a color set by setColor() until another
	/// call to setColor() changes the drawing color.
	///
	/// \param hexColor The hexidecimal representation of the color to use when
	/// drawing.
	virtual void setHexColor( int hexColor )=0;

	virtual void setBitmapTextMode(ofDrawBitmapMode mode)=0;

	// bg color
	virtual ofColor getBackgroundColor()=0;
	virtual void setBackgroundColor(const ofColor & c)=0;
	virtual void background(const ofColor & c)=0;
	virtual void background(float brightness)=0;
	virtual void background(int hexColor, float _a=255.0f)=0;
	virtual void background(int r, int g, int b, int a=255)=0;

	virtual void setBackgroundAuto(bool bManual)=0;	// default is true
	virtual bool getBackgroundAuto()=0;

	virtual void clear()=0;
	virtual void clear(float r, float g, float b, float a=0)=0;
	virtual void clear(float brightness, float a=0)=0;
	virtual void clearAlpha()=0;

	// drawing
	virtual void drawLine(float x1, float y1, float z1, float x2, float y2, float z2) const=0;
	virtual void drawRectangle(float x, float y, float z, float w, float h) const=0;
	virtual void drawTriangle(float x1, float y1, float z1, float x2, float y2, float z2, float x3, float y3, float z3) const=0;
	virtual void drawCircle(float x, float y, float z, float radius) const=0;
	virtual void drawEllipse(float x, float y, float z, float width, float height) const=0;
	virtual void drawString(string text, float x, float y, float z) const=0;
	virtual void drawString(const ofTrueTypeFont & font, string text, float x, float y) const=0;


	// returns true an ofPath to draw with, this allows to keep
	// immediate mode rendering working in multiwindow with multiple
	// contexts without reimplementing the logic on every renderer
	virtual ofPath & getPath()=0;

	virtual ofStyle getStyle() const=0;
	virtual void setStyle(const ofStyle & style) = 0;
	virtual void pushStyle()=0;
	virtual void popStyle()=0;

	virtual void setCurveResolution(int resolution)=0;
	virtual void setPolyMode(ofPolyWindingMode mode)=0;

	virtual const of3dGraphics & get3dGraphics() const=0;
	virtual of3dGraphics & get3dGraphics()=0;


	virtual void setPlaneResolution( int columns, int rows );
	virtual ofVec2f getPlaneResolution() const;
	virtual void drawPlane(float x, float y, float width, float height) const;
	virtual void drawPlane(float x, float y, float z, float width, float height) const;
	virtual void drawPlane(ofPoint& position, float width, float height) const;
	virtual void drawPlane( float width, float height ) const;

	// UV Sphere
	virtual void setSphereResolution(int res);
	virtual int getSphereResolution() const;
	virtual void drawSphere(float x, float y, float radius) const;
	virtual void drawSphere(float x, float y, float z, float radius) const;
	virtual void drawSphere(const ofPoint& position, float radius) const;
	virtual void drawSphere(float radius) const;

	// Ico Sphere
	virtual void setIcoSphereResolution( int res );
	virtual int getIcoSphereResolution() const;
	virtual void drawIcoSphere(float x, float y, float z, float radius) const;
	virtual void drawIcoSphere(float x, float y, float radius) const;
	virtual void drawIcoSphere(const ofPoint& position, float radius) const;
	virtual void drawIcoSphere(float radius) const;

	// Cylinder //
	virtual void setCylinderResolution( int radiusSegments, int heightSegments, int capSegments=2 );
	virtual ofVec3f getCylinderResolution() const;
	virtual void drawCylinder(float x, float y, float radius, float height) const;
	virtual void drawCylinder(float x, float y, float z, float radius, float height) const;
	virtual void drawCylinder(const ofPoint& position, float radius, float height) const;
	virtual void drawCylinder(float radius, float height) const;

	// Cone

	/// \brief Set the resolution of a polygonized cone.
	///
	/// Allows you to set the polygonization resolution of any cones you subsequently draw with ofDrawCone().
	///
	/// \param radiusSegments The number of facets (subdivisions) around the cone's circular footprint.
	/// \param heightSegments The number of subdivisions from the cone's top to bottom.
	/// \param capSegments The number of annular (ring-shaped) subdivisions of the cone's endcap.
	virtual void setConeResolution( int radiusSegments, int heightSegments, int capSegments=2);

	/// \brief Retrieve a data structure describing the resolution with which cones are polygonized.
	///
	/// Allows you to fetch the resolution with which cones are polygonized.
	/// Returns an ofVec3f containing the following data:
	/// Encoded as "x": radiusSegments, the number of facets (subdivisions) around the cone's circular footprint.
	/// Encoded as "y": heightSegments, the number of subdivisions from the cone's top to bottom.
	/// Encoded as "z": capSegments, the number of annular (ring-shaped) subdivisions of the cone's endcap.
	///
	/// \returns An ofVec3f containing (radiusSegments, heightSegments, capSegments) for cone polygonization.
	virtual ofVec3f getConeResolution() const;

	virtual void drawCone(float x, float y, float z, float radius, float height) const;
	virtual void drawCone(float x, float y, float radius, float height) const;
	virtual void drawCone(const ofPoint& position, float radius, float height) const;
	virtual void drawCone(float radius, float height) const;

	// Box
	virtual void setBoxResolution( int res );
	virtual void setBoxResolution( int resWidth, int resHeight, int resDepth );
	virtual ofVec3f getBoxResolution() const;

	/// \brief Draws a rectangular box with the specified dimensions, starting from the specified coordinates.
	///
	/// A box is a rectangular solid: an extruded rectangle.
	/// It is drawn starting from a 3D reference coordinate.
	/// It has a width (in x), a height (in y), and a depth (in z).
	/// The box is drawn with the current color, e.g. set with ofSetColor().
	/// The box is drawn filled by default; change this with ofFill();
	///
	/// \param x The x-coordinate of the box's origin.
	/// \param y The y-coordinate of the box's origin.
	/// \param z The z-coordinate of the box's origin.
	/// \param width The width of the box.
	/// \param height The height of the box.
	/// \param depth The depth of the box.
	virtual void drawBox( float x, float y, float z, float width, float height, float depth) const;

	/// \brief Draws a cube with the specified size, starting from the specified coordinates.
	///
	/// A cube is a rectangular solid bounded by six square faces of equal size.
	/// It is also known as a regular hexahedron, a square parallelepiped, an equilateral cuboid
	/// and a right rhombohedron. It is a regular square prism in three orientations.
	///
	/// It is drawn starting from a 3D reference coordinate, with the specified size.
	/// The cube is drawn with the current color, e.g. set with ofSetColor().
	/// The cube is drawn filled by default; change this with ofFill();
	///
	/// \param x The x-coordinate of the cube's origin.
	/// \param y The y-coordinate of the cube's origin.
	/// \param z The z-coordinate of the cube's origin.
	/// \param size The size of the cube.
	virtual void drawBox(float x, float y, float z, float size) const;

	/// \brief Draws a rectangular box with the specified dimensions, starting from the specified position.
	///
	/// A box is a rectangular solid: an extruded rectangle.
	/// It is drawn starting from a 3D reference coordinate.
	/// It has a width (in x), a height (in y), and a depth (in z).
	/// The box is drawn with the current color, e.g. set with ofSetColor().
	/// The box is drawn filled by default; change this with ofFill();
	///
	/// \param position an ofPoint which contains the (x,y,z) coordinates for the box's reference corner.
	/// \param width The width of the box.
	/// \param height The height of the box.
	/// \param depth The depth of the box.
	virtual void drawBox(const ofPoint& position, float width, float height, float depth) const;

	/// \brief Draws a cube with the specified size, starting from the specified position.
	///
	/// A cube is drawn starting from a 3D reference position, with the specified size.
	/// The cube is drawn with the current color, e.g. set with ofSetColor().
	/// The cube is drawn filled by default; change this with ofFill();
	///
	/// \param position an ofPoint which contains the (x,y,z) coordinates for the cube's reference corner.
	/// \param size The size of the cube.
	virtual void drawBox(const ofPoint& position, float size) const;

	/// \brief Draws a cube with the specified size, starting from the origin.
	///
	/// The cube is drawn with the current color, e.g. set with ofSetColor().
	/// The cube is drawn filled by default; change this with ofFill();
	///
	/// \param size The size of the cube.
	virtual void drawBox(float size) const;

	/// \brief Draws a rectangular box with the specified dimensions, starting from the origin.
	///
	/// A box is a rectangular solid: an extruded rectangle.
	/// It is drawn starting from the origin of the current reference frame.
	/// It has a width (in x), a height (in y), and a depth (in z).
	/// The box is drawn with the current color, e.g. set with ofSetColor().
	/// The box is drawn filled by default; change this with ofFill();
	///
	/// \param width The width of the box.
	/// \param height The height of the box.
	/// \param depth The depth of the box.
	virtual void drawBox( float width, float height, float depth ) const;

	virtual void drawAxis(float size) const;
	virtual void drawGrid(float stepSize, size_t numberOfSteps, bool labels, bool x, bool y, bool z) const;
	virtual void drawGridPlane(float stepSize, size_t numberOfSteps, bool labels) const;
	virtual void drawArrow(const ofVec3f& start, const ofVec3f& end, float headSize) const;
	virtual void drawRotationAxes(float radius, float stripWidth, int circleRes) const;
};

class ofBaseGLRenderer: public ofBaseRenderer{
public:
	using ofBaseRenderer::draw;
	virtual void draw(const ofTexture & image, float x, float y, float z, float w, float h, float sx, float sy, float sw, float sh) const=0;
	virtual void draw(const ofVbo & vbo, GLuint drawMode, int first, int total) const=0;
	virtual void drawElements(const ofVbo & vbo, GLuint drawMode, int amt, int offsetelements) const=0;
	virtual void drawInstanced(const ofVbo & vbo, GLuint drawMode, int first, int total, int primCount) const=0;
	virtual void drawElementsInstanced(const ofVbo & vbo, GLuint drawMode, int amt, int primCount) const=0;
	virtual void draw(const ofVboMesh & mesh, ofPolyRenderMode renderType) const=0;
	virtual void drawInstanced(const ofVboMesh & mesh, ofPolyRenderMode renderType, int primCount) const=0;


	virtual void enableTextureTarget(const ofTexture & tex, int textureLocation)=0;
	virtual void disableTextureTarget(int textureTarget, int textureLocation)=0;
	virtual void setAlphaMaskTex(const ofTexture & tex)=0;
	virtual void disableAlphaMask()=0;
	virtual void enablePointSprites()=0;
	virtual void disablePointSprites()=0;

	// lighting
	virtual void enableLighting()=0;
	virtual void disableLighting()=0;
	virtual void enableSeparateSpecularLight()=0;
	virtual void disableSeparateSpecularLight()=0;
	virtual bool getLightingEnabled()=0;
	virtual void setSmoothLighting(bool b)=0;
	virtual void setGlobalAmbientColor(const ofColor& c)=0;
	virtual void enableLight(int lightIndex)=0;
	virtual void disableLight(int lightIndex)=0;
	virtual void setLightSpotlightCutOff(int lightIndex, float spotCutOff)=0;
	virtual void setLightSpotConcentration(int lightIndex, float exponent)=0;
	virtual void setLightAttenuation(int lightIndex, float constant, float linear, float quadratic )=0;
	virtual void setLightAmbientColor(int lightIndex, const ofFloatColor& c)=0;
	virtual void setLightDiffuseColor(int lightIndex, const ofFloatColor& c)=0;
	virtual void setLightSpecularColor(int lightIndex, const ofFloatColor& c)=0;
	virtual void setLightPosition(int lightIndex, const ofVec4f & position)=0;
	virtual void setLightSpotDirection(int lightIndex, const ofVec4f & direction)=0;

	virtual int getGLVersionMajor()=0;
	virtual int getGLVersionMinor()=0;

	virtual void saveScreen(int x, int y, int w, int h, ofPixels & pixels)=0;
	virtual void saveFullViewport(ofPixels & pixels)=0;

	// bindings
	using ofBaseRenderer::bind;
	using ofBaseRenderer::unbind;
	virtual void bind(const ofBaseMaterial & material)=0;
	virtual void bind(const ofShader & shader)=0;
	virtual void bind(const ofTexture & texture, int location)=0;
	virtual void bind(const ofBaseVideoDraws & video)=0;
	virtual void unbind(const ofBaseMaterial & material)=0;
	virtual void unbind(const ofShader & shader)=0;
	virtual void unbind(const ofTexture & texture, int location)=0;
	virtual void unbind(const ofBaseVideoDraws & video)=0;
	virtual void bind(const ofFbo & fbo)=0;
	virtual void unbind(const ofFbo & fbo)=0;
#ifndef TARGET_OPENGLES
	virtual void bindForBlitting(const ofFbo & fboSrc, ofFbo & fboDst, int attachmentPoint=0)=0;
#endif
	virtual void begin(const ofFbo & fbo, bool setupPerspective)=0;
	virtual void end(const ofFbo & fbo)=0;

};


class ofBaseSerializer{
public:
	virtual ~ofBaseSerializer(){}

	virtual void serialize(const ofAbstractParameter & parameter)=0;
	virtual void deserialize(ofAbstractParameter & parameter)=0;
};

class ofBaseFileSerializer: public ofBaseSerializer{
public:
	virtual ~ofBaseFileSerializer(){}

	virtual bool load(const string & path)=0;
	virtual bool save(const string & path)=0;
};

class ofBaseURLFileLoader{
public:
	virtual ~ofBaseURLFileLoader(){};
	virtual ofHttpResponse get(const string& url)=0;
	virtual int getAsync(const string& url, const string& name="")=0;
	virtual ofHttpResponse saveTo(const string& url, const string& path)=0;
	virtual int saveAsync(const string& url, const string& path)=0;
	virtual void remove(int id)=0;
	virtual void clear()=0;
	virtual void stop()=0;
	virtual ofHttpResponse handleRequest(ofHttpRequest request) = 0;
};

class ofBaseMaterial{
public:
	virtual ~ofBaseMaterial(){};
	virtual ofFloatColor getDiffuseColor() const=0;
	virtual ofFloatColor getAmbientColor() const=0;
	virtual ofFloatColor getSpecularColor() const=0;
	virtual ofFloatColor getEmissiveColor() const=0;
	virtual float getShininess() const=0;
	virtual void begin() const=0;
	virtual void end() const=0;
	virtual const ofShader & getShader(int textureTarget, ofGLProgrammableRenderer & renderer) const=0;
	virtual void uploadMatrices(const ofShader & shader,ofGLProgrammableRenderer & renderer) const;
	virtual void updateMaterial(const ofShader & shader,ofGLProgrammableRenderer & renderer) const=0;
	virtual void updateLights(const ofShader & shader,ofGLProgrammableRenderer & renderer) const=0;
};
