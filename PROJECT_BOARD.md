# ThinkCPP Project Board

Numbered tasks for tracking work. Each task has a permanent number; add new tasks at the end. Update status as work progresses.

### Current focus (2026-10-10)

- **Task 1:** Releases — see below.

---

## Task 1: Releases (PDF on GitHub and greenteapress.com)

**Status:** Ongoing (added 2026-10-10)

### Released

- **v1.1.0** (tag only) — `c743149`, the source matching the PDF built 2019-05-16.
- **v1.1.1** (2026-10-10) — `c334d3c`: the 2020–2022 contributor typo fixes, plus restoring "one of the operands is a string" (cha7). 191 pages. Same file on greenteapress.com.
- **v1.1.2** (2026-10-10, latest) — the copyright page's license link now matches its text: `creativecommons.org/licenses/by-nc-sa/4.0/` (CC BY-NC-SA 4.0; it linked BY-NC 4.0). Allen's decision. Same file on greenteapress.com.

### How to release a new version

The pattern (GreenTeaPress `PROJECT_BOARD.md`, Task 7): the GitHub release asset is the canonical, versioned PDF; an identical copy lives on greenteapress.com (the WordPress page links that copy, which opens in the browser); the two must be the same file.

1. **Bump the version** (`\date {Version X.Y.Z}` in `book/main.tex` (chapters are `book/cha*.tex`, `app*.tex`)) and commit the source changes.
2. **Build** in a clean copy (not in a working tree with stray files): copy `book/`, then `latex main; makeindex main; latex main; latex main; dvips -Ppdf -o thinkCScpp.ps main; ps2pdf` with the Makefile's `PDFFLAGS` → `thinkCScpp.pdf` (book class, no fancyhdr)
3. **Check the build:** no `^!` errors or "Rerun" warnings in the log; same page count unless content changed; compare the text with the previous PDF and read every difference:
   `diff <(pdftotext OLD.pdf - | tr -s ' \n' ' ') <(pdftotext NEW.pdf - | tr -s ' \n' ' ')` (or line-by-line `pdftotext` + `diff`); render any page that looks suspicious (`pdftoppm -f N -l N -r 60 -png`).
   
4. **Commit and push** the source (and anything the repo keeps in git); note the full SHA: `git rev-parse HEAD`.
5. **greenteapress.com:** `cp thinkCScpp.pdf ~/GreenTeaPress/greenteapress/thinkcpp/`; in `~/GreenTeaPress`: commit, `scripts/deploy_gtp.sh -n thinkcpp/thinkCScpp.pdf`, then without `-n`; check `curl -s https://greenteapress.com/thinkcpp/thinkCScpp.pdf | cmp - greenteapress/thinkcpp/thinkCScpp.pdf`.
6. **GitHub release:** `gh release create vX.Y.Z ~/GreenTeaPress/greenteapress/thinkcpp/thinkCScpp.pdf -R AllenDowney/ThinkCPP --target FULL_SHA --title "Think C++, version X.Y.Z" --notes-file NOTES.md --latest` (`--target` needs the **full** SHA). Verify: `curl -sL https://github.com/AllenDowney/ThinkCPP/releases/latest/download/thinkCScpp.pdf | cmp - ~/GreenTeaPress/greenteapress/thinkcpp/thinkCScpp.pdf`.
7. Record the release here and in GreenTeaPress Task 7. Download counts for release assets are archived weekly by `~/GreenTeaPress/scripts/github_traffic.py`; GTP downloads appear in the weekly log report.

---

