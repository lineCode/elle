#ifndef  ELLE_UTILITY_BUFFERSTREAM_HH
# define ELLE_UTILITY_BUFFERSTREAM_HH

# include <iosfwd>
# include <elle/utility/fwd.hh>
# include <elle/utility/Buffer.hh>

namespace elle
{
  namespace utility
  {

    class InputBufferStream
    {
    private:
      WeakBuffer        _buffer;
      size_t            _idx;

    public:
      InputBufferStream(WeakBuffer const& input);
      InputBufferStream(InputBufferStream const& other);

      size_t BytesLeft() const;
      size_t Offset() const     { return this->_idx; }

    /// The following methods make this class "std::istream like".
    public:
      void read(char* out, std::streamsize size);

    };

    class OutputBufferStream
    {
    private:
      Buffer&       _buffer;

    public:
      OutputBufferStream(Buffer& output);
      OutputBufferStream(OutputBufferStream const& other);

    /// The following methods make this class "std::ostream like".
    public:
      void write(char const* out, std::streamsize size);
    };

  }
}

#endif
