# CLI Quick Logger for Obsidian
The aim here is to be able to quickly append to a markdown table with things like Date Time autofill, filling multiple rows at once, and quickly setting and forgetting settings for a specific log.

### Usage:
In {xdg-config-home}/qwklg.json map columns to shell functions, plain text or the @arg keyword for in user input your markdown table.
For Example
qwklog.json
```json
{
  "hotdogs": {
    "$path": "/home/hotdog_lover3254/hotdogs.md"
    "time eaten": "$(date)",
    "amount eaten": "@arg",
    "condiments": "relish",
  }
}
```
shell command
```bash
qwklog hotdogs 1
```
This will find the markdown file file in path and append a row to the first table with these 3 matching rows (case sensitive exact string match).
