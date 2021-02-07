#pragma once
#include <boost/filesystem.hpp>
#include <unordered_set>
#include "Validators/IFileValidator.hpp"

namespace fs = boost::filesystem;
using strings = std::vector<std::string>;
using unique_strings = std::unordered_set<std::string>;

/**
 * Класс занимается поиском файлов в заданных каталогах (paths) на заданную глубину вложенности (depth).
 * Фильтры (валидаторы) на поиск добавляются через add_validator. Применяются последовательно.
 * Возвращает результаты через итераторы.
 * */
class FileFinder : public std::enable_shared_from_this<FileFinder>
{
    // Класс итераторов должен иметь доступ к приватным валидаторам.
    friend class FileFinderIterator;
    // Класс билдера должен иметь доступ к приватному конструктору.
    friend class FileFinderBuilder;
    
    /**
     * Класс итераторов.
     * Применяет фильтры и выдаёт найденные объекты.
     * */
    class FileFinderIterator : public std::forward_iterator_tag
    {
    public:
        FileFinderIterator() = delete;
        explicit FileFinderIterator(std::shared_ptr<FileFinder> file_finder) noexcept;
        void operator++() noexcept;
        const di& operator*() const noexcept;
        bool operator!=(const FileFinderIterator &) const noexcept;

    private:
        // Вспомогательный метод проверки глубины поиска. Помогает уменьшить проверки при рекурсивном поиске.
        void control_depth(di &it) noexcept;
        // Проходит ли найденный объект все фильтры поиска?
        [[nodiscard]] bool is_valid_file(const di&) const noexcept;
        // Обязательная проверка для всех объектов, после которой остальные фильтры не нужно проверять.
        [[nodiscard]] bool is_end(const di&) const noexcept;

    private:
        // Ссылка на объект поиска.
        std::shared_ptr<FileFinder> finder;
        // Хранит текущее состояние поиска.
        di current;
        // Итератор на текущий корневой каталог поиска.
        unique_strings::const_iterator directory;

        // Закешированное значение конца поиска.
        static inline const di end_iterator;
    };

public:
    FileFinder() = delete;
    FileFinder(FileFinder &&) = delete;

    /**
     * Добавление фильтра поиска. Применяются в порядке добавления.
     * Так как фильтры могут быть переиспользованы, используем shared_ptr.
     * */
    FileFinder* add_validator(std::shared_ptr<IFileValidator>) noexcept;

    /**
     * Получение результатов поиска происходит через итераторы.
     * */
    FileFinderIterator begin();
    FileFinderIterator end();

private:
    /**
     * Объект можно создавать только через shared_ptr.
     * Чтобы исключить возможность случайного создания объекта без shared_ptr,
     * это разрешено делать только FileFinderBuilder через friend.
     * */
    FileFinder(const strings &paths, size_t depth) noexcept;

private:
    // Список каталогов поиска.
    const unique_strings directories;
    // Глубина поиска. 0 - только указанные каталоги без вложенности.
    size_t depth = 0;

    // Валидаторы(фильтры) поиска.
    std::vector<std::shared_ptr<IFileValidator>> validators;
};
