[![Open in Visual Studio Code](https://classroom.github.com/assets/open-in-vscode-c66648af7eb3fe8bc4f294546bfd86ef473780cde1dea487d3c4ff354943c9ae.svg)](https://classroom.github.com/online_ide?assignment_repo_id=9194626&assignment_repo_type=AssignmentRepo)
# GSL: Beginning

## Основная цель

Реализация контейнеров, алгоритмов, сущностей стандартной библиотеки с применением ООП, ориентируясь на решения STL. 

### Опорная диаграмма классов
![](https://upload.wikimedia.org/wikipedia/commons/c/c0/Diagramme_UML_de_STL.png?uselang=ru)
## Первый этап

- Изучить структуру репозитория:
  - Организацию файлов, папок
  - Организацию библиотек и структуру классов\интерфейсов

- Реализовать `gsl::array, gsl::vector, gsl::linked_list` - первые контейнеры
- Реализовать покрытие тестами (минимальное - `95%`)

#### Примечание

Метод to_string для различных контейнеров:
- sequence container `[1, 2, 3, 4, 5]`
- associative container `{key:value, key:value, key:value}`
- set container `{value, value, value, value, value}`
- pair `(key, value)`
- tuple `(value [type], value [type], value [type], value [type], value [type])`
- optional `value [type]` или `nullopt`
- variant `value [type]` или `bad_variant_access`
- any `value [type]` или `bad_any_cast`

