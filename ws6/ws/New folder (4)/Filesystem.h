#ifndef SDDS_FILESYSTEM_H
#define SDDS_FILESYSTEM_H
#include "Directory.h"
#include "File.h"
namespace sdds {
   class Filesystem {
      Directory* m_root{};
      Directory* m_current{};
      int count;
   public:
      Filesystem(std::string fileName, std::string rootDirectoryName="");
      Filesystem(const Filesystem& F) = delete;
      Filesystem& operator=(const Filesystem& F) = delete;
      Filesystem(Filesystem&& F) noexcept;
      Filesystem& operator=(Filesystem&& F) noexcept;
      Filesystem& operator+=(Resource*);
      Directory* change_directory(const std::string& dir="");
      Directory* get_current_directory() const;
      ~Filesystem();
   };
}
#endif // !SDDS_FILESYSTEM_H